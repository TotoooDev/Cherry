#pragma once

#include <ImGui/imgui.h>
#include <GLFW/glfw3.h>
#include <string>
#include <filesystem>

namespace Utils
{
	std::string SaveFileDialog(const char* filter, GLFWwindow* window);
	std::string OpenFileDialog(const char* filter, GLFWwindow* window);
	std::string OpenFolderDialog();

	std::wstring StringToWString(const std::string& str);
    std::string WStringToString(const std::wstring& wstr);

	std::string FileName(const std::filesystem::directory_entry& dirEntry);
	std::string FileName(const std::string& path);

	ImFont* GetDefaultFontWithScale(float scale);
}