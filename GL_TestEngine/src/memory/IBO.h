#pragma once

#include <GL/glew.h>

namespace engine {
	class IBO {
	public:
		IBO();
		~IBO();

		void putData(const GLuint* data, GLuint count);
		void bind() const;
		void unbind() const;

		inline const GLuint getID() { return m_rendererID; }
		inline const GLuint getCount() { return m_count; }

	private:
		GLuint m_rendererID = 0;
		GLuint m_count = 0;

	};
}