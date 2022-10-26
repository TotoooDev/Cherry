#include <Panels/Start.h>
#include <Utils.h>
#include <IconFontCppHeaders/IconsMaterialDesign.h>

StartPanel::StartPanel(ImGuiConfig* config)
	: m_Config(config)
{
	// This is temporary
	m_LargeFont = m_Config->GetImFont(FontIndex::UI);
	m_MediumFont = m_Config->GetImFont(FontIndex::UI);
}

void StartPanel::Draw(bool* isOpen)
{
	ImGui::Begin("Get started", isOpen);

	ImGui::PushFont(m_LargeFont);
	ImGui::SameLine(64.0f);
	ImGui::Text("\nCherry");
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
	ImGui::NewLine();

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 16.0f));

	ImGui::SameLine(128.0f);
	m_New = ImGui::Button(ICON_MD_DESCRIPTION " New file");
	ImGui::NewLine();
	ImGui::SameLine(128.0f);
	m_Open = ImGui::Button(ICON_MD_FILE_OPEN " Open file");
	ImGui::NewLine();
	ImGui::SameLine(128.0f);
	m_OpenFolder = ImGui::Button(ICON_MD_FOLDER_OPEN " Open folder");

	ImGui::PopStyleVar();

	ImGui::End();
}