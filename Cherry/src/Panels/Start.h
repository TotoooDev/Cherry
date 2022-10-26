#pragma once

#include <ImGuiConfig.h>
#include <ImGui/imgui.h>

class StartPanel
{
public:
	StartPanel(ImGuiConfig* config);

	void Draw(bool* isOpen);

	bool New() { return m_New; }
	bool Open() { return m_Open; }
	bool OpenFolder() { return m_OpenFolder; }

private:
	ImGuiConfig* m_Config;

	ImFont* m_LargeFont;
	ImFont* m_MediumFont;

	bool m_New = false, m_Open = false, m_OpenFolder = false;
};