#pragma once

#include <Window.h>
#include <ImGui/imgui.h>

class ImGuiConfig
{
public:
	ImGuiConfig(Window* window);
	~ImGuiConfig();

	void Begin();
	void End();

private:
	void SetImGuiTheme();

	Window* m_Window;
};