#include <App.h>
#include <ImGui/imgui.h>
#include <vector>

App::App(const WindowSpecification& spec)
	: m_Window(spec)
{
	auto lang = TextEditor::LanguageDefinition::CPlusPlus();
	m_Editor.SetLanguageDefinition(lang);
	m_Editor.SetShowWhitespaces(false);
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
			{ }
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();

		ImGui::Begin("Editor", &m_ShowEditor);
		auto cpos = m_Editor.GetCursorPosition();
		ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, m_Editor.GetTotalLines(),
			m_Editor.IsOverwrite() ? "Ovr" : "Ins",
			m_Editor.CanUndo() ? "*" : " ",
			m_Editor.GetLanguageDefinition().mName.c_str(), "bonjour.txt");
		m_Editor.Render("TextEditor");
		ImGui::End();

		m_Window.EndImGui();

		m_Window.Swap();
	}
}