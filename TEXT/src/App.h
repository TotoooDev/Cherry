#pragma once

#include <Window.h>
#include <Panels/Browser.h>
#include <ImGui/TextEditor.h>

class App
{
public:
	App(const WindowSpecification& spec);
	~App() = default;

	void Run();

private:
	// TODO: Change this to an event system
	void HandleInputs();
	
	void New();
	void Open();
	void OpenFolder();
	void Save();
	void SaveAs();
	void SaveAll();

	Window m_Window;

	struct EditorPanel
	{
		TextEditor Editor;
		std::string Path;
		std::string Name;
		bool IsOpen = true;
		bool Edited = false;
	};

	std::vector<EditorPanel> m_Editors;
	unsigned int m_FocusedWindow;

	bool m_ShowBrowserPanel = true;
	BrowserPanel m_BrowserPanel;
};