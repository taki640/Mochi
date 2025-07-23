#include "SystemDialogs.hpp"

#include <algorithm>

#ifdef MOCHI_WINDOWS
#include <Windows.h>
#endif

namespace Mochi
{
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

	bool OpenFileDialog(std::wstring& outPath, void* nativeWindow, std::span<const FileDialogFilter> filters, int filterIndex, bool normalizePath)
	{
	#ifdef MOCHI_WINDOWS
		OPENFILENAMEW openFileName;
		WCHAR sizeFile[MAX_PATH] = { 0 }; // TODO: Long path aware (https://learn.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation)
		ZeroMemory(&openFileName, sizeof(OPENFILENAMEW));
		openFileName.lStructSize = sizeof(OPENFILENAMEW);
		openFileName.hwndOwner = (HWND)nativeWindow;
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

	bool OpenFileDialogUTF8(std::string& outPath, void* nativeWindow, std::span<const FileDialogFilter> filters, int filterIndex, bool normalizePath)
	{
		std::wstring widePath;
		if (OpenFileDialog(widePath, nativeWindow, filters, filterIndex, normalizePath))
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
}
