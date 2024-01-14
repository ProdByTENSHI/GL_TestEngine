#pragma once

#include "VBO.h"
#include "VertexBufferLayout.h"

namespace engine {
	class VAO {
	public:
		VAO();
		~VAO();

		void addBuffer(const VBO& vbo, const VertexBufferLayout& layout);

		void bind() const;
		void unbind() const;

	private:
		GLuint m_rendererID;

	};
}