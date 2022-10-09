#pragma once

#include <Window.h>
#include <Panels/Editor.h>

class App
{
public:
	App(const WindowSpecification& spec);
	~App() = default;

	void Run();

private:
	Window m_Window;

	bool m_ShowEditor = true;
	EditorPanel m_Editor;
};