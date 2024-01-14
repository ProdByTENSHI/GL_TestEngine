#pragma once

#include <GL/glew.h>

namespace engine {
	class VBO {
	public:
		VBO();
		~VBO();

		void putData(const void* data, GLuint size);
		void bind() const;
		void unbind() const;

		inline const GLuint getID() { return m_rendererID; }

	private:
		GLuint m_rendererID = 0;

	};
}