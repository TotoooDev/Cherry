#include <Panels/Editor.h>
#include <ImGui/imgui.h>

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
	m_Editor.Render("TextEditor");

	ImGui::End();
}