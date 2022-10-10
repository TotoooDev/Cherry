#include <Panels/Browser.h>
#include <ImGui/imgui.h>
#include <filesystem>

void BrowserPanel::Draw(bool* isOpen)
{
	std::filesystem::current_path(m_CurrentPath);

	ImGui::Begin("File browser", isOpen);

	RecurseFolders(m_CurrentPath, false);

	ImGui::End();
}

void BrowserPanel::RecurseFolders(std::string path, bool treeNodeOpened)
{
	std::filesystem::current_path(path);

	for (auto const& dirEntry : std::filesystem::directory_iterator("."))
	{
		if (dirEntry.is_directory())
		{
			std::string newPath = std::filesystem::current_path().string() + "\\" + dirEntry.path().string();
			bool treeNode = ImGui::TreeNode(newPath.c_str());
			if (treeNode)
				RecurseFolders(newPath, treeNode);
		}
		else
			ImGui::Text(std::filesystem::path(dirEntry.path().string()).string().c_str());
	}

	if (treeNodeOpened)
		ImGui::TreePop();
}