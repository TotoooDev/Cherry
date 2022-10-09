#pragma once

#include <ImGui/imgui.h>
#include <string>

class EditorPanel
{
public:
	EditorPanel();

	void Draw(bool* isOpen);

private:
	static int TextEditCallback(ImGuiInputTextCallbackData* data);

	static void ExpandText();

	static char* m_Text;
	static unsigned int m_Size;
	static std::string m_Name;
};