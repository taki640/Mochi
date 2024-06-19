#include "Image.hpp"

#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "Utils.hpp"

namespace Mochi
{
	Image::Image(std::string_view path, bool flipY)
	{
		Load(path, flipY);
	}

	Image::Image(const uint8_t* buffer, int bufferSize, bool flipY)
	{
		Load(buffer, bufferSize, flipY);
	}

	Image::~Image()
	{
		DeleteTexture();
	}

	void Image::Load(std::string_view path, bool flipY)
	{
		stbi_set_flip_vertically_on_load(flipY);
		stbi_uc* data = stbi_load(path.data(), &m_Width, &m_Height, &m_Channels, 0);
		CreateTexture(data);
	}

	void Image::Load(const uint8_t* buffer, int bufferSize, bool flipY)
	{
		stbi_set_flip_vertically_on_load(flipY);
		stbi_uc* data = stbi_load_from_memory(buffer, bufferSize, &m_Width, &m_Height, &m_Channels, 0);
		CreateTexture(data);
	}

	void Image::CreateTexture(void* data)
	{
		GLenum format = 0;
		if (m_Channels == 4)
			format = GL_RGBA;
		else if (m_Channels == 3)
			format = GL_RGB;
		else if (m_Channels == 1)
			format = GL_RED;

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}

	void Image::DeleteTexture()
	{
		if (IsLoaded())
		{
			glDeleteTextures(1, &m_TextureID);
			m_TextureID = 0;
		}
	}
}
