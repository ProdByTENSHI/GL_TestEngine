#include "VBO.h"

namespace memory {
	VBO::VBO() {
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	}

	VBO::~VBO() {
		glDeleteBuffers(1, &m_rendererID);
	}

	void VBO::putData(const void* data, GLuint size) {
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void VBO::bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	}

	void VBO::unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}