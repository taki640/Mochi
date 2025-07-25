#include "SystemDialogs.hpp"

#include <algorithm>

#ifdef MOCHI_WINDOWS
#include <Windows.h>

// Use Windows 8+ message box style
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif


namespace Mochi
{
#ifdef MOCHI_WINDOWS
	static HWND g_WindowHWND;

	void RegisterDialogsHWND(HWND hwnd)
	{
		g_WindowHWND = hwnd;
	}
#endif

	static std::wstring BuildFileDialogWindowsFilter(std::span<const FileDialogFilter> filters)
	{
		std::wstring result;

		for (const FileDialogFilter& filter : filters)
		{
			if (filter.Description == nullptr || filter.Extensions.empty())
				continue;

			bool hasNullExtension = false;
			for (const wchar_t* ext : filter.Extensions)
			{
				if (ext == nullptr)
				{
					hasNullExtension = true;
					break;
				}
			}

			if (hasNullExtension)
				continue;

			result += filter.Description;
			result += L'\0';

			for (size_t i = 0; i < filter.Extensions.size(); ++i)
			{
				if (filter.Extensions[i] == nullptr)
					continue;

				result += filter.Extensions[i];
				if (i < filter.Extensions.size() - 1)
					result += L';';
			}

			result += L'\0';
		}

		result += L'\0';
		return result;
	}

	bool OpenFileDialog(std::wstring& outPath, std::span<const FileDialogFilter> filters, int filterIndex, bool normalizePath)
	{
	#ifdef MOCHI_WINDOWS
		OPENFILENAMEW openFileName;
		WCHAR sizeFile[MAX_PATH] = { 0 }; // TODO: Long path aware (https://learn.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation)
		ZeroMemory(&openFileName, sizeof(OPENFILENAMEW));
		openFileName.lStructSize = sizeof(OPENFILENAMEW);
		openFileName.hwndOwner = g_WindowHWND;
		openFileName.lpstrFile = sizeFile;
		openFileName.nMaxFile = sizeof(sizeFile);

		std::wstring filter = BuildFileDialogWindowsFilter(filters);
		openFileName.lpstrFilter = filter.empty() ? nullptr : filter.c_str();
		openFileName.nFilterIndex = filterIndex + 1;	// nFilterIndex starts at 1

		openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileNameW(&openFileName) == TRUE)
		{
			outPath = openFileName.lpstrFile;
			if (normalizePath)
				std::replace(outPath.begin(), outPath.end(), '\\', '/');
			return true;
		}
	#endif

		return false;
	}

	bool OpenFileDialogUTF8(std::string& outPath, std::span<const FileDialogFilter> filters, int filterIndex, bool normalizePath)
	{
		std::wstring widePath;
		if (OpenFileDialog(widePath, filters, filterIndex, normalizePath))
		{
		#ifdef MOCHI_WINDOWS
			int size = WideCharToMultiByte(CP_UTF8, 0, widePath.data(), (int)widePath.size(), nullptr, 0, nullptr, nullptr);
			outPath.resize(size);
			WideCharToMultiByte(CP_UTF8, 0, widePath.data(), (int)widePath.size(), outPath.data(), size, nullptr, nullptr);
			return true;
		#endif
		}

		return false;
	}

	bool OpenFileDialog(std::vector<std::wstring>& outPaths, std::span<const FileDialogFilter> filters, int filterIndex, bool normalizePaths)
	{
	#ifdef MOCHI_WINDOWS
		std::vector<WCHAR> buffer(65536, 0);

		OPENFILENAMEW openFileName;
		ZeroMemory(&openFileName, sizeof(OPENFILENAMEW));
		openFileName.lStructSize = sizeof(OPENFILENAMEW);
		openFileName.hwndOwner = g_WindowHWND;
		openFileName.lpstrFile = buffer.data();
		openFileName.nMaxFile = (DWORD)buffer.size();

		std::wstring filter = BuildFileDialogWindowsFilter(filters);
		openFileName.lpstrFilter = filter.empty() ? nullptr : filter.c_str();
		openFileName.nFilterIndex = filterIndex + 1;

		openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR | OFN_ALLOWMULTISELECT | OFN_EXPLORER;

		if (GetOpenFileNameW(&openFileName) == TRUE)
		{
			const WCHAR* ptr = buffer.data();
			std::wstring directory = ptr;
			ptr += directory.size() + 1;

			wchar_t dirSeparator;
			if (normalizePaths)
			{
				std::replace(directory.begin(), directory.end(), '\\', '/');
				dirSeparator = L'/';
			}
			else
			{
				dirSeparator = L'\\';
			}

			if (*ptr == 0)
			{
				outPaths.push_back(std::move(directory));
			}
			else
			{
				while (*ptr)
				{
					outPaths.emplace_back(directory + dirSeparator + ptr);
					ptr += wcslen(ptr) + 1;
				}
			}

			return true;
		}
	#endif

		return false;
	}

	bool OpenFileDialogUTF8(std::vector<std::string>& outPaths, std::span<const FileDialogFilter> filters, int filterIndex, bool normalizePaths)
	{
		std::vector<std::wstring> widePaths;
		if (OpenFileDialog(widePaths, filters, filterIndex, normalizePaths))
		{
		#ifdef MOCHI_WINDOWS
			for (const std::wstring& widePath : widePaths)
			{
				std::string& outPath = outPaths.emplace_back();
				int size = WideCharToMultiByte(CP_UTF8, 0, widePath.data(), (int)widePath.size(), nullptr, 0, nullptr, nullptr);
				outPath.resize(size);
				WideCharToMultiByte(CP_UTF8, 0, widePath.data(), (int)widePath.size(), outPath.data(), size, nullptr, nullptr);
			}

			return true;
		#endif
		}

		return false;
	}

	// Imagine how amazing the world would be if Microsoft programmers prefixed their macros with WIN_ 
#undef ERROR

	static uint32_t GetMessageBoxType(MessageBoxType type)
	{
	#ifdef MOCHI_WINDOWS
		switch (type)
		{
			case MessageBoxType::INFO:		return MB_ICONINFORMATION;
			case MessageBoxType::WARNING:	return MB_ICONWARNING;
			case MessageBoxType::ERROR:		return MB_ICONERROR;
		}
	#endif

		return 0;
	}

	void ShowMessageBox(const std::string& message, const std::string& caption, MessageBoxType type)
	{
	#ifdef MOCHI_WINDOWS
		MessageBoxA(g_WindowHWND, message.data(), caption.data(), GetMessageBoxType(type));
	#endif
	}

	void ShowMessageBox(const std::wstring& message, const std::wstring& caption, MessageBoxType type)
	{
	#ifdef MOCHI_WINDOWS
		MessageBoxW(g_WindowHWND, message.data(), caption.data(), GetMessageBoxType(type));
	#endif
	}
}
