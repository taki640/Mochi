#pragma once

#include "../../Source/Base.hpp"

#define MOCHI_INVALID_TEXTURE_ID 0xFFFFFFFF

namespace Mochi
{
	class Image
	{
	public:
		Image() = default;
		Image(std::string_view path, bool flipY = false);
		Image(const uint8_t* buffer, int bufferSize, bool flipY = false);
		~Image();

		void Load(std::string_view path, bool flipY = false);
		void Load(const uint8_t* buffer, int bufferSize, bool flipY = false);

		inline uint32_t ID() const { return m_TextureID; }
		inline bool IsLoaded() const { return m_TextureID != MOCHI_INVALID_TEXTURE_ID; }
	private:
		uint32_t m_TextureID = MOCHI_INVALID_TEXTURE_ID;
		int m_Width = 0;
		int m_Height = 0;
		int m_Channels = 0;

		void CreateTexture(void* data);
		void DeleteTexture();
	};
}
