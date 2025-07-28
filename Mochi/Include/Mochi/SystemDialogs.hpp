#pragma once

#include "../../Source/Base.hpp"

#include <vector>
#include <span>

namespace Mochi
{
	struct FileDialogFilter
	{
		const wchar_t* Description = nullptr; // E.g. Image files
		std::span<const wchar_t*> Extensions; // E.g. { *.png, *.jpg, *.jpeg, *.gif }
	};

	bool OpenFileDialog(std::wstring& outPath, std::span<const FileDialogFilter> filters = std::span<const FileDialogFilter>(), int filterIndex = 0, bool normalizePath = false);
	bool OpenFileDialogUTF8(std::string& outPath, std::span<const FileDialogFilter> filters = std::span<const FileDialogFilter>(), int filterIndex = 0, bool normalizePath = false);

	bool OpenFileDialog(std::vector<std::wstring>& outPaths, std::span<const FileDialogFilter> filters = std::span<const FileDialogFilter>(), int filterIndex = 0, bool normalizePaths = false);
	bool OpenFileDialogUTF8(std::vector<std::string>& outPaths, std::span<const FileDialogFilter> filters = std::span<const FileDialogFilter>(), int filterIndex = 0, bool normalizePaths = false);

	bool SaveFileDialog(std::wstring& outPath, const wchar_t* defaultExtension = nullptr, std::span<const FileDialogFilter> filters = std::span<const FileDialogFilter>(), int filterIndex = 0, bool normalizePath = false);
	bool SaveFileDialogUTF8(std::string& outPath, const char* defaultExtension = nullptr, std::span<const FileDialogFilter> filters = std::span<const FileDialogFilter>(), int filterIndex = 0, bool normalizePath = false);

	enum class MessageBoxType
	{
		INFO,
		WARNING,
		ERROR
	};

	void ShowMessageBox(const std::string& message, const std::string& caption, MessageBoxType type);
	void ShowMessageBox(const std::wstring& message, const std::wstring& caption, MessageBoxType type);
}
