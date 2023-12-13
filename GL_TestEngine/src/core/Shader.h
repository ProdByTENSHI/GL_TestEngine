#pragma once

#include <unordered_map>
#include <string>

#include <gl/glew.h>

namespace core {
	constexpr unsigned int INVALID_SHADER = 0xFFFFF;

	class Shader {
	public:
		Shader();
		// Create a Shader from external Shader Source Files
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		// Create Shader from Vertex Shader Source and Fragment Shader Source
		void create(const std::string& vertexSource, const std::string& fragmentSource);
		void bind();
		void unbind();

		// Load a Shader Source File and return it's source code
		const std::string loadShader(const std::string& path);

		// Set Uniforms
		void setUniform1i(const std::string& name, int value);
		void setUniform1f(const std::string& name, float value);
		void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

		inline GLuint getProgram() { return m_program; }

	private:
		GLuint compileShader(GLuint type, const std::string& source);
		GLint getUniformLocation(const std::string& name);

		GLuint m_program = 0;
		GLuint m_vertexShader = 0;
		GLuint m_fragmentShader = 0;

		std::unordered_map<std::string, GLint> m_uniformLocationCache;
	};
}