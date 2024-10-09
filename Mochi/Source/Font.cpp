#include "Font.hpp"

#include <imgui.h>

namespace Mochi
{
	BaseFont::BaseFont(float fontSize) : m_FontSize(fontSize)
	{
	}

	MemoryFont::MemoryFont(uint8_t* buffer, int bufferSize, float fontSize, bool deleteBuffer) :
		m_Buffer(buffer), m_BufferSize(bufferSize), m_DeleteBuffer(deleteBuffer), BaseFont(fontSize)
	{
	}

	MemoryFont::~MemoryFont()
	{
		if (m_DeleteBuffer)
			delete m_Buffer;
	}

	void MemoryFont::Load() const
	{
		ImFontConfig config;
		config.FontDataOwnedByAtlas = false;
		ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)m_Buffer, m_BufferSize, m_FontSize, &config);
	}

	FileFont::FileFont(std::string_view filePath, float fontSize) :
		m_FilePath(filePath), BaseFont(fontSize)
	{
	}

	void FileFont::Load() const
	{
		ImGui::GetIO().Fonts->AddFontFromFileTTF(m_FilePath.data(), m_FontSize);
	}
}
