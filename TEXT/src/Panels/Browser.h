#pragma once

#include <Panels/Editor.h>
#include <vector>
#include <string>

class BrowserPanel
{
public:
	BrowserPanel(std::vector<std::pair<EditorPanel, bool>>* editors, const std::string& path = "");

	void Draw(bool* isOpen);
	
	void SetCurrentPath(const std::string& path) { m_CurrentPath = path; }

private:
	void RecurseFolders(std::string path, bool treeNodeOpened);

	std::string m_CurrentPath;
	std::string m_SelectedPath;

	std::vector<std::pair<EditorPanel, bool>>* m_Editors;
};