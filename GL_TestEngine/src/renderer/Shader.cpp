#include "Shader.h"

#include <iostream>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>
#include "logger/Logger.h"

namespace engine {
	Shader::Shader() {}

	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
		: m_program(0), m_vertexShader(0), m_fragmentShader(0) {
		std::string vertexSource = loadShader(vertexPath);
		std::string fragmentSource = loadShader(fragmentPath);

		create(vertexSource, fragmentSource);

		Logger::getInstance()->write("Loaded Shader " + vertexPath + " : " + fragmentPath);
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

			Logger::getInstance()->write(typeStr + " : " + errorMessage);

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

	void Shader::setUniform3f(const std::string& name, float v0, float v1, float v2) {
		glUniform3f(getUniformLocation(name), v0, v1, v2);
	}

	void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
		glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
	}

	void Shader::setUniformMat4(const std::string& name, const glm::mat4& mat) {
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
	}

	GLint Shader::getUniformLocation(const std::string& name) {
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
			return m_uniformLocationCache[name];

		GLint location = glGetUniformLocation(m_program, name.c_str());
		if (location == -1) {
			std::cerr << "WARNING: Uniform '" << name << "' does not exist" << std::endl;
			GLint count;
			glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &count);
			for (int i = 0; i < count; i++) {
				char name[100];
				glGetActiveUniformName(m_program, i, sizeof(name), (GLsizei*)NULL, name);
				std::cout << "Active Uniforms: " << name << std::endl;
			}
		} else
			m_uniformLocationCache.insert(std::make_pair(name, location));

		return location;
	}
}