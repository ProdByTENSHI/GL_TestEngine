#pragma once

#include <string>
#include <GL/glew.h>

#include "stb_image.h"

namespace model {
	class Texture {
	public:
		Texture(const std::string& path);
		~Texture();

		void bind(unsigned int slot = 0) const;
		void unbind() const;

		void free();

		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }

	private:
		std::string m_filePath;
		GLuint m_textureBuffer = 0;

		unsigned char* m_data;

		int m_bpp;		// Base-per-Pixel
		int m_width;
		int m_height;
	};
}