#include <App.h>
#include <Utils.h>
#include <Keycode.h>
#include <ImGui/imgui.h>
#include <vector>
#include <fstream>
#include <iostream>

App::App(const WindowSpecification& spec)
	: m_Window(spec)
{
	m_BrowserPanel.SetCurrentPath("C:\\Users\\nanog\\Documents\\Test TEXT");
}

void App::Run()
{
	while (!m_Window.ShouldClose())
	{
		m_Window.PollEvents();
		HandleInputs();

		m_Window.BeginImGui();

		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		// Epic ImGui stuff here
		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New", "Ctrl+N"))
				New();

			ImGui::Separator();

			if (ImGui::MenuItem("Open...", "Ctrl+O"))
				Open();
			if (ImGui::MenuItem("Open folder...", "Ctrl+Shift+O"))
				OpenFolder();

			ImGui::Separator();

			if (ImGui::MenuItem("Save", "Ctrl+S"))
				Save();
			if (ImGui::MenuItem("Save as...", "Ctrl+Shift+S"))
				SaveAs();
			if (ImGui::MenuItem("Save all..."))
				SaveAll();

			ImGui::Separator();

			if (ImGui::MenuItem("Quit", "Alt+F4"))
				m_Window.Close();

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();

		for (unsigned int i = 0; i < m_Editors.size(); i++)
		{
			EditorPanel& editor = m_Editors[i];
			if (editor.IsOpen)
			{
				if (editor.Editor.IsTextChanged())
					editor.Edited = true;
				ImGuiWindowFlags flags = editor.Edited ? ImGuiWindowFlags_UnsavedDocument : ImGuiWindowFlags_None;

				ImGui::Begin(editor.Name.c_str(), &editor.IsOpen, flags);

				if (ImGui::IsWindowFocused())
					m_FocusedWindow = i;

				auto cpos = editor.Editor.GetCursorPosition();
				ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, editor.Editor.GetTotalLines(),
					editor.Editor.IsOverwrite() ? "Ovr" : "Ins",
					editor.Editor.CanUndo() ? "*" : " ",
					editor.Editor.GetLanguageDefinition().mName.c_str(), editor.Path.c_str());
				editor.Editor.Render("TextEditor");

				ImGui::End();
			}
		}

		if (m_ShowBrowserPanel)
			m_BrowserPanel.Draw(&m_ShowBrowserPanel);

		m_Window.EndImGui();

		m_Window.Swap();
	}
}

void App::HandleInputs()
{
	if (m_Window.Key(TOE_KEY_LEFT_CONTROL) || m_Window.Key(TOE_KEY_RIGHT_CONTROL))
	{
		if (m_Window.Key(TOE_KEY_LEFT_SHIFT) || m_Window.Key(TOE_KEY_RIGHT_SHIFT))
		{
			if (m_Window.Key(TOE_KEY_O))
				OpenFolder();
			if (m_Window.Key(TOE_KEY_S))
				SaveAs();
		}
		if (m_Window.Key(TOE_KEY_N))
			New();
		if (m_Window.Key(TOE_KEY_O))
			Open();
		if (m_Window.Key(TOE_KEY_S))
			Save();
	}
}

void App::New()
{
	EditorPanel editor;
	editor.Name = "Unnamed document";
	editor.Editor.SetShowWhitespaces(false);
	m_Editors.push_back(editor);
}

void App::Open()
{
	std::string path = Utils::OpenFileDialog("All files\0*.*\0", m_Window.GetNativeWindow());
	if (!path.empty())
	{
		EditorPanel editor;
		editor.Path = path;
		std::ifstream t(path);
		if (t.good())
		{
			std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
			editor.Editor.SetText(str);
			editor.Editor.SetShowWhitespaces(false);
			editor.Editor.SetTextChanged(false);
		}
		editor.Name = path.substr(path.find_last_of("\\"));
		editor.Name.erase(0, 1);
		m_Editors.push_back(editor);
	}
}

void App::OpenFolder()
{
	std::string path = Utils::OpenFolderDialog();
	m_BrowserPanel.SetCurrentPath(path);
}

void App::Save()
{
	EditorPanel& editor = m_Editors[m_FocusedWindow];
	if (editor.Path.empty())
	{
		SaveAs();
		return;
	}
	std::ofstream file(editor.Path);
	file << editor.Editor.GetText();
	editor.Edited = false;
}

void App::SaveAs()
{
	EditorPanel& editor = m_Editors[m_FocusedWindow];
	std::string path = Utils::SaveFileDialog("All files\0*.*\0", m_Window.GetNativeWindow());
	if (!path.empty())
	{
		editor.Path = path;
		editor.Name = path.substr(path.find_last_of("\\"));
		editor.Name.erase(0, 1);
		std::ofstream file(editor.Path);
		file << editor.Editor.GetText();
		editor.Edited = false;
	}
}

void App::SaveAll()
{
	for (unsigned int i = 0; i < m_Editors.size(); i++)
	{
		m_FocusedWindow = i;
		Save();
	}
}