#include <Panels/Editor.h>

EditorPanel::EditorPanel(const std::string& path, const std::string& name)
	: m_Path(path), m_Name(name)
{

}

void EditorPanel::Draw(bool* isOpen)
{
	if (m_Editor.IsTextChanged())
		m_Edited = true;
	ImGuiWindowFlags flags = m_Edited ? ImGuiWindowFlags_UnsavedDocument : ImGuiWindowFlags_None;

	ImGui::Begin(m_Name.c_str(), isOpen, flags);

	m_IsFocused = ImGui::IsWindowFocused();

	auto cpos = m_Editor.GetCursorPosition();
	ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, m_Editor.GetTotalLines(),
		m_Editor.IsOverwrite() ? "Ovr" : "Ins",
		m_Editor.CanUndo() ? "*" : " ",
		m_Editor.GetLanguageDefinition().mName.c_str(), m_Path.c_str());
	m_Editor.Render("TextEditor");

	ImGui::End();
}