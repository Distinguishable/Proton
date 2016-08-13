#include "shader.h"

namespace proton {
	namespace base {
		namespace shader {
			Shader::Shader(const char* vertPath, const char* fragPath) :
				pr_VertPath(vertPath), pr_FragPath(fragPath)
			{
				pr_ShaderID = load();
			}

			Shader::~Shader() {
				glDeleteProgram(pr_ShaderID);
			}

			GLuint Shader::load() {
				GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
				GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

				std::string VertexShaderCode;
				std::ifstream VertexShaderStream(pr_VertPath, std::ios::in);
				if (VertexShaderStream.is_open()) {
					std::string Line = "";
					while (getline(VertexShaderStream, Line))
						VertexShaderCode += "\n" + Line;
					VertexShaderStream.close();
				}
				else {
					printf("Impossible to open %s. \n", pr_VertPath);
					getchar();
					return 0;
				}

				std::string FragmentShaderCode;
				std::ifstream FragmentShaderStream(pr_FragPath, std::ios::in);
				if (FragmentShaderStream.is_open()) {
					std::string Line = "";
					while (getline(FragmentShaderStream, Line))
						FragmentShaderCode += "\n" + Line;
					FragmentShaderStream.close();
				}

				GLint Result = GL_FALSE;
				int InfoLogLength;


				printf("Compiling shader : %s\n", pr_VertPath);
				char const * VertexSourcePointer = VertexShaderCode.c_str();
				glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
				glCompileShader(VertexShaderID);

				glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
				glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
				if (InfoLogLength > 0) {
					std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
					glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
					printf("%s\n", &VertexShaderErrorMessage[0]);
				}



				printf("Compiling shader : %s\n", pr_FragPath);
				char const * FragmentSourcePointer = FragmentShaderCode.c_str();
				glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
				glCompileShader(FragmentShaderID);

				glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
				glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
				if (InfoLogLength > 0) {
					std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
					glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
					printf("%s\n", &FragmentShaderErrorMessage[0]);
				}



				printf("Linking program\n");
				GLuint ProgramID = glCreateProgram();
				glAttachShader(ProgramID, VertexShaderID);
				glAttachShader(ProgramID, FragmentShaderID);
				glLinkProgram(ProgramID);

				glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
				glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
				if (InfoLogLength > 0) {
					std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
					glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
					printf("%s\n", &ProgramErrorMessage[0]);
				}


				glDetachShader(ProgramID, VertexShaderID);
				glDetachShader(ProgramID, FragmentShaderID);

				glDeleteShader(VertexShaderID);
				glDeleteShader(FragmentShaderID);

				return ProgramID;
			}

			void Shader::enable() const {
				glUseProgram(pr_ShaderID);
			}

			void Shader::disable() const {
				glUseProgram(0);
			}

			GLint Shader::getUniformLocation(const GLchar* name) {
				return glGetUniformLocation(pr_ShaderID, name);
			}

			void Shader::setUniform1i(const GLchar* name, int value) {
				glUniform1i(getUniformLocation(name), value);
			}

			void Shader::setUniform1f(const GLchar* name, float value) {
				glUniform1f(getUniformLocation(name), value);
			}
			void Shader::setUniform2f(const GLchar* name, glm::vec2 value) {
				glUniform2f(getUniformLocation(name), value.x, value.y);
			}
			void Shader::setUniform3f(const GLchar* name, glm::vec3 value) {
				glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
			}

			void Shader::setUniform4f(const GLchar* name, glm::vec4 value) {
				glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
			}

			void Shader::setUniformMat4(const GLchar* name, const glm::mat4 matrix) {
				glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
			}
		}
	}
}