#include <Panels/Start.h>
#include <Utils.h>
#include <IconFontCppHeaders/IconsMaterialDesign.h>

StartPanel::StartPanel()
{
	m_LargeFont = Utils::GetDefaultFontWithScale(64.0f);
	m_MediumFont = Utils::GetDefaultFontWithScale(32.0f);
}

void StartPanel::Draw(bool* isOpen)
{
	ImGui::Begin("Get started", isOpen);

	ImGui::PushFont(m_LargeFont);
	ImGui::SameLine(64.0f);
	ImGui::Text("TEXT");
	ImGui::PopFont();

	ImGui::NewLine();

	ImGui::PushFont(m_MediumFont);
	ImGui::SameLine(64.0f);
	ImGui::Text("The editor you never needed");

	ImGui::Separator();

	ImGui::Text("\n\n");
	ImGui::NewLine();
	ImGui::SameLine(64.0f);
	ImGui::Text("Get Started: \n");
	ImGui::PopFont();

	ImGui::NewLine();
	ImGui::SameLine(80.0f);
	m_New = ImGui::Button(ICON_MD_DESCRIPTION "New file");
	ImGui::NewLine();
	ImGui::SameLine(80.0f);
	m_Open = ImGui::Button(ICON_MD_FILE_OPEN "Open file");
	ImGui::NewLine();
	ImGui::SameLine(80.0f);
	m_OpenFolder = ImGui::Button(ICON_MD_FOLDER_OPEN "Open folder");

	ImGui::End();
}