#include "IBO.h"

namespace memory {
	IBO::IBO() {
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	}

	IBO::~IBO() {
		glDeleteBuffers(1, &m_rendererID);
	}

	void IBO::putData(const GLuint* data, GLuint count) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
	}

	void IBO::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	}

	void IBO::unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}