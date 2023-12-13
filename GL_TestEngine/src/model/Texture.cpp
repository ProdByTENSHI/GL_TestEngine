#include "Texture.h"

#include <iostream>

namespace model {
	Texture::Texture(const std::string& path)
		: m_filePath(path) {
		stbi_set_flip_vertically_on_load(1);

		m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);
		if (!m_data) {
			std::cerr << "Could not load texture from path " << path << std::endl;
		}

		glGenTextures(1, &m_textureBuffer);
		glBindTexture(GL_TEXTURE_2D, m_textureBuffer);

		// Texture Parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Create Texture from loaded Image Data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);

		// Free up resources after usage
		glBindTexture(GL_TEXTURE_2D, 0);
		if (m_data)
			stbi_image_free(m_data);
	}

	Texture::~Texture() {
		free();
	}

	void Texture::bind(unsigned int slot /*= 0*/) const {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_textureBuffer);
	}

	void Texture::unbind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::free() {
		glDeleteTextures(1, &m_textureBuffer);
	}
}