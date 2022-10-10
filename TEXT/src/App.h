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

	struct EditorPanel
	{
		TextEditor Editor;
		std::string Path;
		bool Show;
	};

	std::vector<EditorPanel> m_Editors;
};