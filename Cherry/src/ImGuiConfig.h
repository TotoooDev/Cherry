#pragma once

#include <Window.h>
#include <Config.h>
#include <ImGui/imgui.h>
#include <map>

enum class FontIndex
{
	UI,
	Icons
};

class ImGuiConfig
{
public:
	ImGuiConfig() = default;
	ImGuiConfig(Window* window);
	~ImGuiConfig();

	void Begin();
	void End();

	void SetFontScaleUI(float scale);
	void SetFontScaleEditor(float scale);
	void ChangeFontScaleUI(float amount);
	void ChangeFontScaleEditor(float amount);

	void LoadFont(FontIndex id, float size);
	void ApplyEditorFontScale();
	void RemoveEditorFontScale();

	ImFont* GetImFont(FontIndex id) { return m_FontMap[id]; }
	std::string GetFontPath(FontIndex id);

private:
	void SetImGuiTheme();

	float m_FontScaleUI = 0.4f;
	float m_FontScaleEditor = 0.4f;
	bool m_IsImGuiInit = false;

	Window* m_Window;
	std::map<FontIndex, ImFont*> m_FontMap;
};