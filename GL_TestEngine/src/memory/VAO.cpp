#include "VAO.h"

namespace engine {
	VAO::VAO() {
		glGenBuffers(1, &m_rendererID);
	}
	VAO::~VAO() {
		glDeleteVertexArrays(1, &m_rendererID);
	}

	void VAO::addBuffer(const VBO& vbo, const VertexBufferLayout& layout) {
		// Bind VAO and VBO
		bind();
		vbo.bind();

		// Setup VAO Layout
		const auto& elements = layout.getElements();
		unsigned int offset = 0;

		for (unsigned int i = 0; i < elements.size(); i++) {
			const auto& element = elements[i];

			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
			glEnableVertexAttribArray(i);

			offset += element.count * VertexBufferElement::getSize(element.type);
		}
	}

	void VAO::bind() const {
		glBindVertexArray(m_rendererID);
	}

	void VAO::unbind() const {
		glBindVertexArray(0);
	}
}