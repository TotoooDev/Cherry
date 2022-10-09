#pragma once

#include <Window.h>
#include <ImGui/TextEditor.h>

class App
{
public:
	App(const WindowSpecification& spec);
	~App() = default;

	void Run();

private:
	Window m_Window;

	bool m_ShowEditor = true;
	TextEditor m_Editor;
};