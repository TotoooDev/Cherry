#pragma once

#include <string>

class BrowserPanel
{
public:
	void Draw(bool* isOpen);
	
	void SetCurrentPath(const std::string& path) { m_CurrentPath = path; }

private:
	void RecurseFolders(std::string path, bool treeNodeOpened);

	std::string m_CurrentPath;
};