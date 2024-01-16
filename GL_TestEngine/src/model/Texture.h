#pragma once

#include <string>
#include <GL/glew.h>

#include "TextureData.h"

namespace engine {
	class Texture {
	public:
		Texture(const std::string& path, const std::string& type);
		~Texture();

		void bind(unsigned int slot = 0) const;
		void unbind() const;

		void free();

		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }

		inline TextureData getTextureData() const { return m_textureData; }

	private:
		TextureData m_textureData;

		std::string m_filePath;
		GLuint m_textureBuffer = 0;

		unsigned char* m_data;

		int m_bpp;		// Base-per-Pixel
		int m_width;
		int m_height;
	};
}