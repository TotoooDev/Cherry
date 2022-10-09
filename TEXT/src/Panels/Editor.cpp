#include <Panels/Editor.h>
#include <fstream>

char* EditorPanel::m_Text;
unsigned int EditorPanel::m_Size = 16;
std::string EditorPanel::m_Name = "Unnamed";

EditorPanel::EditorPanel()
{
	m_Text = new char[m_Size];
	memset(m_Text, 0, sizeof(m_Text) - 1);
}

void EditorPanel::Draw(bool* isOpen)
{
	if (*isOpen)
	{
		ImGui::Begin("Editor", isOpen);

		ImGui::InputTextMultiline(" ", m_Text, m_Size, ImGui::GetContentRegionAvail(), ImGuiInputTextFlags_CallbackEdit, &TextEditCallback);

		ImGui::End();
	}
}

int EditorPanel::TextEditCallback(ImGuiInputTextCallbackData* data)
{
	if (data->BufTextLen == m_Size - 1)
		ExpandText();
	return 0;
}

// FIXME: What if the user tries to paste more than 256 characters at once?
void EditorPanel::ExpandText()
{
	std::fstream tempFile;
	tempFile.open("temp/" + m_Name + ".texttemp");
	tempFile << m_Text;

	delete[] m_Text;
	m_Size += 16;
	m_Text = new char[m_Size];

	tempFile >> m_Text;
	tempFile.close();
}