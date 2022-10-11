#pragma once

#include <Window.h>
#include <Panels/Editor.h>
#include <Panels/Browser.h>
#include <Panels/Start.h>
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

	std::vector<std::pair<EditorPanel, bool>> m_Editors;
	EditorPanel* m_FocusedEditor = nullptr;

	bool m_ShowBrowserPanel = true;
	BrowserPanel m_BrowserPanel;
	bool m_ShowStartPanel = true;
	StartPanel m_StartPanel;
};