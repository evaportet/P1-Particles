#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

namespace graphics {
	struct ShaderFiles {
		const std::string vertexShaderPath;
		const std::string geometryShaderPath;
		const std::string fragmentShaderPath;
	};

	struct LayoutAttrib {
		int position;
		char* name;
	};

	class Program {
	private:
		unsigned int m_RendererId;

		ShaderFiles files;
		std::vector<LayoutAttrib> layout;
		std::unordered_map<std::string, unsigned int> locationCache;

		unsigned int UniformLocation(std::string name);
	public:

		Program(ShaderFiles files, std::string name, std::vector<LayoutAttrib> layout);
		~Program();

		void Bind() const;
		void Unbind() const;

		void SetUniform(std::string name, glm::mat4 mat) {
			glUniformMatrix4fv(UniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
		}

		void SetUniform(std::string name, glm::vec4 vec) {
			glUniform4f(UniformLocation(name), vec.x, vec.y, vec.z, vec.w);
		}

		void SetUniform(std::string name, float v) {
			glUniform1f(UniformLocation(name), v);
		}
	};
}