#pragma once

#include <ImGui/imgui.h>
#include <functional>

class StartPanel
{
public:
	StartPanel();

	void Draw(bool* isOpen);

	bool New() { return m_New; }
	bool Open() { return m_Open; }
	bool OpenFolder() { return m_OpenFolder; }

private:
	ImFont* m_LargeFont;
	ImFont* m_MediumFont;

	bool m_New, m_Open, m_OpenFolder;
};