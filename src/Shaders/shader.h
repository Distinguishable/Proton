#pragma once

#include <GL\glew.h>
#include "../FileUtils/ReadFile.h"
#include <vector>
#include <iostream>
#include <glm\glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace proton {
	namespace base {
		namespace shader {
			class Shader {
			private:
				GLuint pr_ShaderID;

				const char* pr_VertPath;
				const char* pr_FragPath;
			public:
				Shader(const char* vertPath, const char* fragPath);
				~Shader();


				void setUniform1i(const GLchar* name, int value);
				void setUniform1f(const GLchar* name, float value);
				void setUniform2f(const GLchar* name, glm::vec2 value);
				void setUniform3f(const GLchar* name, glm::vec3 value);
				void setUniform4f(const GLchar* name, glm::vec4 value);

				void setUniformMat4(const GLchar* name, const glm::mat4 matrix);

				void enable() const;
				void disable() const;
			private:
				GLuint load();
				GLint getUniformLocation(const GLchar* name);
			};
		}
	}
}