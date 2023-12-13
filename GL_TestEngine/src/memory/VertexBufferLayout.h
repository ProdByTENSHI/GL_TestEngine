#pragma once

#include <vector>

#include <GL/glew.h>

namespace memory {
	struct VertexBufferElement {
		GLuint type;
		GLuint count;
		GLboolean normalized;

		static unsigned int getSize(unsigned int type) {
			switch (type) {
			case GL_FLOAT: return sizeof(GLfloat);

			case GL_UNSIGNED_INT: return sizeof(GLuint);

			case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
			}

			return 0;
		}
	};

	class VertexBufferLayout {
	public:
		VertexBufferLayout() {}

		template<typename T> void push(unsigned int count) {}

		template<> void push<GLfloat>(unsigned int count) {
			VertexBufferElement element = {
				GL_FLOAT,
				count,
				GL_FALSE
			};

			m_elements.push_back(element);
			m_stride += VertexBufferElement::getSize(GL_FLOAT) * count;
		}

		template<> void push<GLuint>(unsigned int count) {
			VertexBufferElement element = {
				GL_UNSIGNED_INT,
				count,
				GL_FALSE
			};

			m_elements.push_back(element);
			m_stride += VertexBufferElement::getSize(GL_UNSIGNED_INT) * count;
		}

		template<> void push<GLubyte>(unsigned int count) {
			VertexBufferElement element = {
				GL_UNSIGNED_BYTE,
				count,
				GL_TRUE
			};

			m_elements.push_back(element);
			m_stride += VertexBufferElement::getSize(GL_UNSIGNED_BYTE) * count;
		}

		inline const std::vector<VertexBufferElement> getElements() const { return m_elements; }
		inline GLuint getStride() const { return m_stride; }

	private:
		GLuint m_stride = 0;

		std::vector<VertexBufferElement> m_elements;
	};
}