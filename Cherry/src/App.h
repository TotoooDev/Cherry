#pragma once

#include <Window.h>
#include <ImGuiConfig.h>
#include <Panels/Editor.h>
#include <Panels/Browser.h>
#include <Panels/Start.h>
#include <Panels/Markdown.h>
#include <ImGuiColorTextEdit/TextEditor.h>

class App
{
public:
	App(const WindowSpecification& spec);
	~App() = default;

	void Run();

private:
	void CreateDockspace();
	void DrawMenuBar();
	// TODO: Change this to an event system
	void HandleInputs();
	
	void New();
	void Open();
	void OpenFolder();
	void Save();
	void SaveAs();
	void SaveAll();

	std::string m_ApplicationPath;
	std::string m_WorkingDir;

	Window m_Window;
	bool m_IsRunning = true;

	ImGuiConfig m_ImGuiConfig;
	bool m_IncreaseFontUI = false;
	bool m_DecreaseFontUI = false;
	bool m_IncreaseFontEditor = false;
	bool m_DecreaseFontEditor = false;

	std::vector<std::pair<EditorPanel, bool>> m_Editors;
	EditorPanel* m_FocusedEditor = nullptr;

	bool m_ShowBrowserPanel = true;
	BrowserPanel m_BrowserPanel;
	bool m_ShowStartPanel = true;
	StartPanel m_StartPanel;
};