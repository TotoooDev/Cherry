#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace Utils
{
	std::string SaveFileDialog(const char* filter, GLFWwindow* window);
	std::string OpenFileDialog(const char* filter, GLFWwindow* window);
	std::string OpenFolderDialog();

	std::wstring StringToWString(const std::string& str);
    std::string WStringToString(const std::wstring& wstr);
}