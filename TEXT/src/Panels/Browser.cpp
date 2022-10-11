#include <Panels/Browser.h>
#include <Utils.h>
#include <ImGui/imgui.h>
#include <IconFontCppHeaders/IconsMaterialDesign.h>
#include <fstream>

BrowserPanel::BrowserPanel(std::vector<std::pair<EditorPanel, bool>>* editors, const std::string& path)
	:  m_Editors(editors), m_CurrentPath(path)
{

}

void BrowserPanel::Draw(bool* isOpen)
{
	if (!m_CurrentPath.empty())
		std::filesystem::current_path(m_CurrentPath);

	ImGui::Begin("File browser", isOpen);

	if (!m_CurrentPath.empty() && ImGui::TreeNodeEx(Utils::FileName(m_CurrentPath).c_str(), ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen))
	{
		RecurseFolders(m_CurrentPath, false);
		ImGui::TreePop();
	}

	ImGui::End();
}

void BrowserPanel::RecurseFolders(std::string path, bool treeNodeOpened)
{
	std::filesystem::current_path(path);

	for (auto const& dirEntry : std::filesystem::directory_iterator("."))
	{
		std::filesystem::current_path(path);
		if (dirEntry.is_directory())
		{
			std::string newPath = std::filesystem::current_path().string() + "\\" + Utils::FileName(dirEntry);
			std::string displayName = ICON_MD_FOLDER " " + Utils::FileName(newPath);
			bool treeNode = ImGui::TreeNodeEx(displayName.c_str(), ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_FramePadding);
			if (treeNode)
				RecurseFolders(newPath, treeNode);
		}
		else
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_FramePadding;
			if (dirEntry.path().string() == m_SelectedPath)
				flags |= ImGuiTreeNodeFlags_Selected;
			std::string displayName = ICON_MD_DESCRIPTION " " + Utils::FileName(dirEntry);
			if (ImGui::TreeNodeEx(displayName.c_str(), flags))
			{
				if (ImGui::IsItemClicked())
				{
					m_SelectedPath = dirEntry.path().string();
					bool exists = false;
					for (auto&& [editor, isOpen] : *m_Editors)
					{
						if (m_SelectedPath == editor.GetPath())
						{
							if (!isOpen)
								isOpen = true;
							exists = true;
							break;
						}
					}
					if (!exists)
					{
						EditorPanel editor(dirEntry.path().string(), Utils::FileName(dirEntry));
						std::ifstream t(editor.GetPath());
						if (t.good())
						{
							std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
							editor.GetEditor().SetText(str);
							editor.GetEditor().SetShowWhitespaces(false);
							editor.GetEditor().SetTextChanged(false);
							m_Editors->push_back({ editor, true });
						}
					}
				}
				ImGui::TreePop();
			}
		}
	}

	if (treeNodeOpened)
		ImGui::TreePop();
}