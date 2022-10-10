#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

struct WindowSpecification
{
	std::string Title;
	unsigned int Width;
	unsigned int Height;
};

class Window
{
public:
	Window(const WindowSpecification& spec);
	~Window();

	WindowSpecification GetSpec() { return m_Spec; }
	GLFWwindow* GetNativeWindow() { return m_NativeWindow; }

	void BeginImGui();
	void EndImGui();
	void PollEvents() { glfwPollEvents(); }
	void Swap() { glfwSwapBuffers(m_NativeWindow); }
	bool ShouldClose() { return glfwWindowShouldClose(m_NativeWindow); }

private:
	void SetImGuiTheme();

	WindowSpecification m_Spec;
	GLFWwindow* m_NativeWindow;
};