#include "Font.hpp"

#include <imgui.h>

namespace Mochi
{
	BaseFont::BaseFont(float fontSize) : m_FontSize(fontSize)
	{
	}

	MemoryFont::MemoryFont(const uint8_t* buffer, int bufferSize, float fontSize, bool isCompressed, bool deleteBuffer) :
		m_Buffer(buffer), m_BufferSize(bufferSize), m_IsCompressed(isCompressed), m_DeleteBuffer(deleteBuffer), BaseFont(fontSize)
	{
	}

	MemoryFont::~MemoryFont()
	{
		// In case Load() was never called
		if (m_DeleteBuffer)
			delete m_Buffer;
	}

	void MemoryFont::Load()
	{
		ImFontConfig config;
		config.FontDataOwnedByAtlas = false;

		if (m_IsCompressed)
			ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF((void*)m_Buffer, m_BufferSize, m_FontSize, &config);
		else
			ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)m_Buffer, m_BufferSize, m_FontSize, &config);

		if (m_DeleteBuffer)
		{
			delete m_Buffer;
			m_Buffer = nullptr;
		}
	}

	FileFont::FileFont(std::string_view filePath, float fontSize) :
		m_FilePath(filePath), BaseFont(fontSize)
	{
	}

	void FileFont::Load()
	{
		ImGui::GetIO().Fonts->AddFontFromFileTTF(m_FilePath.data(), m_FontSize);
	}
}
