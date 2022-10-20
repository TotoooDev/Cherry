#include <Utils.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <commdlg.h>
#include <windows.h>
#include <shobjidl_core.h>
#include <string>
#include <sstream>
#include <codecvt>

namespace Utils
{
	std::string SaveFileDialog(const char* filter, GLFWwindow* window)
	{
		OPENFILENAMEA openFileName;
		CHAR szFile[260] = { 0 };
		ZeroMemory(&openFileName, sizeof(OPENFILENAME));
		openFileName.lStructSize = sizeof(OPENFILENAME);
		openFileName.hwndOwner = glfwGetWin32Window(window);
		openFileName.lpstrFile = szFile;
		openFileName.nMaxFile = sizeof(szFile);
		openFileName.lpstrFilter = filter;
		openFileName.nFilterIndex = 1;
		openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetSaveFileNameA(&openFileName) == TRUE)
		{
			return openFileName.lpstrFile;
		}
		return "";
	}

	std::string OpenFileDialog(const char* filter, GLFWwindow* window)
	{
		OPENFILENAMEA openFileName;
		CHAR szFile[260] = { 0 };
		ZeroMemory(&openFileName, sizeof(OPENFILENAME));
		openFileName.lStructSize = sizeof(OPENFILENAME);
		openFileName.hwndOwner = glfwGetWin32Window(window);
		openFileName.lpstrFile = szFile;
		openFileName.nMaxFile = sizeof(szFile);
		openFileName.lpstrFilter = filter;
		openFileName.nFilterIndex = 1;
		openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileNameA(&openFileName) == TRUE)
		{
			return openFileName.lpstrFile;
		}
		return "";
	}

	// I don't even understand what is happening here but it works
	// I should really learn about the Windows API
	std::string OpenFolderDialog()
	{
		IFileOpenDialog* pFileOpen;

		// Create the FileOpenDialog object.
		HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			// Set options so we can only select an existing folder
			FILEOPENDIALOGOPTIONS options;
			pFileOpen->GetOptions(&options);
			options |= FOS_PICKFOLDERS | FOS_PATHMUSTEXIST;
			pFileOpen->SetOptions(options);
			// Show the Open dialog box.
			hr = pFileOpen->Show(NULL);

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileOpen->GetFolder(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					// Convert from wide string to regular string
					std::wstringstream ss;
					ss << pszFilePath;
					std::string path = WStringToString(ss.str());

					pItem->Release();

					return path;
				}
			}
			pFileOpen->Release();
		}

		return "";
	}

	std::wstring StringToWString(const std::string& str)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
		return conv.from_bytes(str);
	}
	std::string WStringToString(const std::wstring& wstr)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
		return conv.to_bytes(wstr);
	}

	std::string FileName(const std::filesystem::directory_entry& dirEntry)
	{
		return std::filesystem::path(dirEntry).filename().string();
	}
	std::string FileName(const std::string& path)
	{
		return std::filesystem::path(path).filename().string();
	}

	ImFont* GetDefaultFontWithScale(float scale)
	{
		auto& io = ImGui::GetIO();
		ImFont* font = io.Fonts->AddFontFromFileTTF("fonts/opensans/OpenSans-Regular.ttf", scale);
		return font;
	}
}