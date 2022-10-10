#include <App.h>
#include <Utils.h>
#include <ImGui/imgui.h>
#include <vector>
#include <fstream>

App::App(const WindowSpecification& spec)
	: m_Window(spec)
{

}

void App::Run()
{
	while (!m_Window.ShouldClose())
	{
		m_Window.PollEvents();

		m_Window.BeginImGui();

		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		// Epic ImGui stuff here

		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open...", "Ctrl+O"))
			{ 
				std::string path = Utils::OpenFileDialog("All files\0*.*\0", m_Window.GetNativeWindow());
				EditorPanel editor;
				editor.Path = path;
				m_Editors.push_back(editor);
			}
			if (ImGui::MenuItem("Save", "Ctrl+S"))
			{
				for (auto& editor : m_Editors)
				{
					std::ofstream file(editor.Path);
					file << editor.Editor.GetText();
				}
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();

		for (auto& editor : m_Editors)
		{
			if (editor.Editor.CanRedo())
				editor.Edited = true;
			ImGuiWindowFlags flags = editor.Edited ? ImGuiWindowFlags_UnsavedDocument : ImGuiWindowFlags_None;
			ImGui::Begin(editor.Path.c_str(), &editor.Show, flags);
			auto cpos = editor.Editor.GetCursorPosition();
			ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, editor.Editor.GetTotalLines(),
				editor.Editor.IsOverwrite() ? "Ovr" : "Ins",
				editor.Editor.CanUndo() ? "*" : " ",
				editor.Editor.GetLanguageDefinition().mName.c_str(), editor.Path.c_str());
			editor.Editor.Render("TextEditor");
			editor.Editor.IsTextChanged();
			ImGui::End();
		}

		m_Window.EndImGui();

		m_Window.Swap();
	}
}