#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <vector>

class TriangleApp
{
public:
	void printExtensions();
	void run();
	static constexpr uint32_t windowWidth{ 1280U };
	static constexpr uint32_t windowHeight{ 720U };
private:
	void initWindow();
	void createInstance();
	void initVulkan();
	void mainLoop();
	void cleanup();
	GLFWwindow* window;
	VkInstance instance;
};

int main(int argc, char* argv[])
{
	TriangleApp app;
	app.printExtensions();
	try
	{
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}
	return 0;
}

void TriangleApp::printExtensions()
{
	uint32_t extCount{ 0 };
	vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);

	std::vector<VkExtensionProperties> ext{ extCount };
	vkEnumerateInstanceExtensionProperties(nullptr, &extCount, ext.data());

	std::cout << "Available Instance Extensions:" << std::endl;

	for (const auto& e : ext)
	{
		std::cout << e.extensionName << " v" << e.specVersion << std::endl;
	}
}

void TriangleApp::run()
{
	initVulkan();
	mainLoop();
	cleanup();
}

void TriangleApp::initWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(windowWidth, windowHeight, "Vulkan", nullptr, nullptr);
}

void TriangleApp::createInstance()
{
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "TriangleApp";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	uint32_t glfwExtensionCount{ 0 };
	const char** glfwExtensions{
		glfwGetRequiredInstanceExtensions(&glfwExtensionCount)
	};

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
		throw std::runtime_error("failed to create instance!");
	
}

void TriangleApp::initVulkan()
{
	createInstance();
}

void TriangleApp::mainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}

void TriangleApp::cleanup()
{
	vkDestroyInstance(instance, nullptr);
	glfwDestroyWindow(window);
	glfwTerminate();
}
