#include "Program.h"

#include <GL/glew.h>
#include <cstddef>
#include <cstdio>
#include <fstream>

namespace graphics {
	GLuint compileShader(const char* shaderStr, GLenum shaderType, std::string name = "") {
		GLuint program = glCreateShader(shaderType);
		glShaderSource(program, 1, &shaderStr, NULL);
		glCompileShader(program);
		GLint res;
		glGetShaderiv(program, GL_COMPILE_STATUS, &res);
		if (res == GL_FALSE) {
			glGetShaderiv(program, GL_INFO_LOG_LENGTH, &res);
			char* buff = new char[res];
			glGetShaderInfoLog(program, res, &res, buff);
			fprintf(stderr, "Error Shader %s: %s", name, buff);
			delete[] buff;
			glDeleteShader(program);
			return 0;
		}
		return program;
	}

	GLuint loadAndCompileShader(std::string path, GLenum shaderType, std::string name = "") {
		std::ifstream stream(path);
		if (!stream.is_open()) {
			fprintf(stderr, "Could not open shader file %s\n", path);
			return 0;
		}
		std::string content(
			(std::istreambuf_iterator<char>(stream)),
			(std::istreambuf_iterator<char>())
		);

		return compileShader(content.c_str(), shaderType, name);
	}

	void linkProgram(GLuint program) {
		glLinkProgram(program);
		GLint res;
		glGetProgramiv(program, GL_LINK_STATUS, &res);
		if (res == GL_FALSE) {
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &res);
			char* buff = new char[res];
			glGetProgramInfoLog(program, res, &res, buff);
			fprintf(stderr, "Error Link: %s", buff);
			delete[] buff;
		}
	}

	Program::Program(ShaderFiles files, std::string name, std::vector<LayoutAttrib> layout) : files(files), layout(layout) {
		GLuint vertexShader, geometryShader, fragmentShader;

		m_RendererId = glCreateProgram();

		vertexShader = loadAndCompileShader(files.vertexShaderPath, GL_VERTEX_SHADER, name + "Vert");
		glAttachShader(m_RendererId, vertexShader);

		if (!files.geometryShaderPath.empty()) {
			geometryShader = loadAndCompileShader(files.geometryShaderPath, GL_GEOMETRY_SHADER, name + "Geom");
			glAttachShader(m_RendererId, geometryShader);
		}

		fragmentShader = loadAndCompileShader(files.fragmentShaderPath, GL_FRAGMENT_SHADER, name + "Frag");
		glAttachShader(m_RendererId, fragmentShader);

		for (auto& attrib : layout) {
			glBindAttribLocation(m_RendererId, attrib.position, attrib.name);
		}

		linkProgram(m_RendererId);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if (!files.geometryShaderPath.empty()) glDeleteShader(geometryShader);
	}

	Program::~Program() {
		glDeleteProgram(m_RendererId);
	}

	void Program::Bind() const {
		glUseProgram(m_RendererId);
	}

	void Program::Unbind() const {
		glUseProgram(0);
	}

	unsigned int Program::UniformLocation(std::string name) {
		auto loc = locationCache.find(name);
		if (loc != locationCache.end()) {
			return loc->second;
		}

		unsigned int newLoc = glGetUniformLocation(m_RendererId, name.c_str());
		locationCache[name] = newLoc;
		return newLoc;
	}

}