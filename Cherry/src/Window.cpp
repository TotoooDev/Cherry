#include <Window.h>
#include <Keycode.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <IconFontCppHeaders/IconsMaterialDesign.h>
#include <iostream>
#include <filesystem>

bool WasGLFWInit = false;
unsigned int NumWindows = 0;

Window::Window(const WindowSpecification& spec)
	: m_Spec(spec)
{
	// Init GLFW
	if (!WasGLFWInit)
	{
		if (glfwInit() == GLFW_FALSE)
		{
			std::cerr << "Failed to initialize GLFW!" << std::endl;
			return;
		}
	}

	// Create the window
	m_NativeWindow = glfwCreateWindow(m_Spec.Width, m_Spec.Height, m_Spec.Title.c_str(), nullptr, nullptr);
	if (!m_NativeWindow)
	{
		std::cerr << "Failed to create window!" << std::endl;
		return;
	}
	glfwMakeContextCurrent(m_NativeWindow);
	glfwSwapInterval(m_Spec.VSync);
	CenterWindow();

	// Init GLEW
	if (!WasGLFWInit)
	{
		glewInit();
		WasGLFWInit = true;
	}

	NumWindows++;
}

Window::~Window()
{
	glfwDestroyWindow(m_NativeWindow);
	NumWindows--;
	// No more windows
	if (NumWindows == 0)
		glfwTerminate();
}

bool Window::Key(int key)
{
	return glfwGetKey(m_NativeWindow, key) == TOE_PRESS;
}

bool Window::MouseButton(int button)
{
	return glfwGetMouseButton(m_NativeWindow, button) == TOE_PRESS;
}

void Window::CenterWindow()
{
	// From https://github.com/glfw/glfw/issues/310

	// Get window position and size
	int window_x, window_y;
	glfwGetWindowPos(m_NativeWindow, &window_x, &window_y);

	int window_width, window_height;
	glfwGetWindowSize(m_NativeWindow, &window_width, &window_height);

	// Halve the window size and use it to adjust the window position to the center of the window
	window_width *= 0.5;
	window_height *= 0.5;

	window_x += window_width;
	window_y += window_height;

	// Get the list of monitors
	int monitors_length;
	GLFWmonitor** monitors = glfwGetMonitors(&monitors_length);

	if (monitors == NULL) {
		// Got no monitors back
		return;
	}

	// Figure out which monitor the window is in
	GLFWmonitor* owner = NULL;
	int owner_x, owner_y, owner_width, owner_height;

	for (int i = 0; i < monitors_length; i++) {
		// Get the monitor position
		int monitor_x, monitor_y;
		glfwGetMonitorPos(monitors[i], &monitor_x, &monitor_y);

		// Get the monitor size from its video mode
		int monitor_width, monitor_height;
		GLFWvidmode* monitor_vidmode = (GLFWvidmode*)glfwGetVideoMode(monitors[i]);

		if (monitor_vidmode == NULL) {
			// Video mode is required for width and height, so skip this monitor
			continue;

		}
		else {
			monitor_width = monitor_vidmode->width;
			monitor_height = monitor_vidmode->height;
		}

		// Set the owner to this monitor if the center of the window is within its bounding box
		if ((window_x > monitor_x && window_x < (monitor_x + monitor_width)) && (window_y > monitor_y && window_y < (monitor_y + monitor_height))) {
			owner = monitors[i];

			owner_x = monitor_x;
			owner_y = monitor_y;

			owner_width = monitor_width;
			owner_height = monitor_height;
		}
	}

	if (owner != NULL) {
		// Set the window position to the center of the owner monitor
		glfwSetWindowPos(m_NativeWindow, owner_x + (owner_width * 0.5) - window_width, owner_y + (owner_height * 0.5) - window_height);
	}
}