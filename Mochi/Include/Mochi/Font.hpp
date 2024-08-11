#pragma once

#include "../../Source/Base.hpp"

namespace Mochi
{
	class BaseFont
	{
	public:
		BaseFont(float fontSize);
		virtual ~BaseFont() = default;

		// Only to be called by Mochi during initialization
		virtual void Load() const = 0;
	protected:
		float m_FontSize = 0.0f;
	};

	// A font from a buffer on memory
	class MemoryFont : public BaseFont
	{
	public:
		MemoryFont() = default;
		MemoryFont(uint8_t* buffer, int bufferSize, float size = 12.0f, bool deleteBuffer = true);
		~MemoryFont();
	private:
		uint8_t* m_Buffer = nullptr;
		int m_BufferSize = 0;
		bool m_DeleteBuffer = false;

		// Make it private in the implementation so client implementations don't mistakenly call it,
		// of course they can still call through a BaseFont* but the chance for mistakes is lower
		virtual void Load() const override;
	};

	// The path for a font on disk
	class FileFont : public BaseFont
	{
	public:
		FileFont() = default;
		FileFont(std::string_view filePath, float size = 12.0f);
	private:
		std::string_view m_FilePath;

		// Make it private in the implementation so client implementations don't mistakenly call it,
		// of course they can still call through a BaseFont* but the chance for mistakes is lower
		virtual void Load() const override;
	};
}
