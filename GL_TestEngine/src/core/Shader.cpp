#include "Shader.h"

#include <iostream>
#include <fstream>

namespace core {
	Shader::Shader() {}

	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
		std::string vertexSource = loadShader(vertexPath);
		std::string fragmentSource = loadShader(fragmentPath);

		create(vertexSource, fragmentSource);
	}

	Shader::~Shader() {
		glDeleteShader(m_vertexShader);
		glDeleteShader(m_fragmentShader);
		glDeleteProgram(m_program);
	}

	GLuint Shader::compileShader(GLuint type, const std::string& source) {
		GLuint id = glCreateShader(type);
		const GLchar* src = source.c_str();

		glShaderSource(id, 1, &src, NULL);
		glCompileShader(id);

		// ERROR HANDLING
		GLint hasCompiled = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			// Type to String to get better Debug Info
			std::string typeStr = "";
			if (type == GL_VERTEX_SHADER)
				typeStr = "Vertex Shader";
			else if (type == GL_FRAGMENT_SHADER)
				typeStr = "Fragment Shader";

			// Get Log Length in Bytes
			GLint logSize = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logSize);

			// Get Log Message
			GLchar errorMessage[1024];
			glGetShaderInfoLog(id, logSize, &logSize, errorMessage);

			std::cout << typeStr << " : " << errorMessage << std::endl;

			glDeleteShader(id);
			return INVALID_SHADER;
		}

		return id;
	}

	void Shader::create(const std::string& vertexSource, const std::string& fragmentSource) {
		m_program = glCreateProgram();
		m_vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
		m_fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

		glAttachShader(m_program, m_vertexShader);
		glAttachShader(m_program, m_fragmentShader);
		glLinkProgram(m_program);
		glValidateProgram(m_program);
	}

	void Shader::bind() {
		glUseProgram(m_program);
	}

	void Shader::unbind() {
		glUseProgram(0);
	}

	const std::string Shader::loadShader(const std::string& path) {
		std::string content;
		std::ifstream stream(path, std::ios::in);

		if (!stream.is_open()) {
			std::cerr << "Could not load File " << path << std::endl;
			return "";
		}

		std::string line = "";
		while (!stream.eof()) {
			std::getline(stream, line);
			content.append(line + "\n");
		}

		stream.close();
		return content;
	}

	void Shader::setUniform1i(const std::string& name, int value) {
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform1f(const std::string& name, float value) {
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
		glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
	}

	GLint Shader::getUniformLocation(const std::string& name) {
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
			return m_uniformLocationCache[name];

		GLint location = glGetUniformLocation(m_program, name.c_str());
		if (location == -1)
			std::cerr << "WARNING: Uniform '" << name << "' does not exist" << std::endl;

		m_uniformLocationCache[name] = location;
		return location;
	}
}