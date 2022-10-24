#pragma once

#include <ImGuiColorTextEdit/TextEditor.h>
#include <filesystem>
#include <string>

class EditorPanel
{
public:
	EditorPanel(const std::string& path = "", const std::string& name = "Unnamed document");

	void Draw(bool* isOpen);

	TextEditor& GetEditor() { return m_Editor; }
	std::string GetPath() const { return m_Path; }
	std::string GetName() const { return m_Name; }
	bool IsEdited() const { return m_Edited; }
	bool IsFocused() const { return m_IsFocused; }
	bool IsPathAbsolute() const { std::filesystem::path path(m_Path); return path.is_absolute(); }

	void SetPath(const std::string& path) { m_Path = path; }
	void SetName(const std::string& name) { m_Name = name; }
	void SetEdited(bool edited) { m_Edited = edited; }

private:
	TextEditor m_Editor;
	std::string m_Path;
	std::string m_Name;
	bool m_Edited = false;
	bool m_IsFocused = false;
};