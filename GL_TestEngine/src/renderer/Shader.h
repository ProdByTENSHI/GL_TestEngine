#pragma once

#include <unordered_map>
#include <string>

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace engine {
	constexpr unsigned int INVALID_SHADER = 0xFFFFF;

	class Shader {
	public:
		Shader();
		// Create a Shader from external Shader Source Files
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		void bind();
		void unbind();

		// Set Uniforms
		GLint getUniformLocation(const std::string& name);

		void setUniform1i(const std::string& name, int value);
		void setUniform1f(const std::string& name, float value);
		void setUniform3f(const std::string& name, float v0, float v1, float v2);
		void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void setUniformMat4(const std::string& name, const glm::mat4& mat);

		inline GLuint getProgram() { return m_program; }

	private:
		// Create Shader from Vertex Shader Source and Fragment Shader Source
		void create(const std::string& vertexSource, const std::string& fragmentSource);

		// Load a Shader Source File and return it's source code
		const std::string loadShader(const std::string& path);

		GLuint compileShader(GLuint type, const std::string& source);

		GLuint m_program = 0;
		GLuint m_vertexShader = 0;
		GLuint m_fragmentShader = 0;

		std::unordered_map<std::string, GLint> m_uniformLocationCache;
	};
}