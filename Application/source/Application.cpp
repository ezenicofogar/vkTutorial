#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

class TriangleApp
{
public:
	void run();
	static constexpr uint32_t windowWidth{ 1280U };
	static constexpr uint32_t windowHeight{ 720U };
private:
	void initWindow();
	void initVulkan();
	void mainLoop();
	void cleanup();
	GLFWwindow* window;
};

int main(int argc, char* argv[])
{
	TriangleApp app;
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

void TriangleApp::initVulkan()
{

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
	glfwDestroyWindow(window);
	glfwTerminate();
}
