#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <iostream>
#include <vector>

#include "../../Buffers/IndexBuffer/IndexBuffer.h"
#include "../../Buffers/VertexArray/VertexArray.h"
#include "../../Buffers./VertexBuffer/VertexBuffer.h"
#include "../../Shaders/shader.h"

namespace proton {
	namespace base {
		namespace renderer {
			struct VertexData {
				glm::vec3 vertex;
				glm::vec2 uv;
				glm::vec3 normal;
			};

			class Model {
			private:
				std::vector<glm::vec3> pr_Vertices;
				std::vector<glm::vec2> pr_TexCoords;
				std::vector<glm::vec3> pr_Normals;
				std::vector<unsigned short> pr_Indices;

				glm::vec3 pr_Position;

				shader::Shader& pr_Shader;

				buffers::VertexArray* pr_VAO;
				buffers::IndexBuffer* pr_IBO;
			public:
				Model(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords, std::vector<glm::vec3> normals, std::vector<unsigned short> indices, glm::vec3 position, shader::Shader& shader)
					: pr_Vertices(vertices), pr_TexCoords(texCoords), pr_Normals(normals), pr_Indices(indices), pr_Position(position), pr_Shader(shader)
				{
					this->pr_VAO = new buffers::VertexArray();

					this->pr_VAO->addBuffer(new buffers::Buffer(vertices, sizeof(vertices) * 3, 3), 0);
					this->pr_VAO->addBuffer(new buffers::Buffer(texCoords, sizeof(texCoords) * 2, 2), 1);
					this->pr_VAO->addBuffer(new buffers::Buffer(normals, sizeof(normals) * 3, 3), 2);

					this->pr_IBO = new buffers::IndexBuffer(indices, indices.size() * 3);
				}

				~Model() {
					delete this->pr_VAO;
					delete this->pr_IBO;
				}

				inline const std::vector<glm::vec3> getVertices() const { return this->pr_Vertices; };
				inline const std::vector<glm::vec2> getTexCoords() const { return this->pr_TexCoords; };
				inline const std::vector<glm::vec3> getNormals() const { return this->pr_Normals; };

				inline const glm::vec3 getPosition() const { return this->pr_Position; }

				inline const std::vector<unsigned short> getIndices() const { return this->pr_Indices; };

				inline shader::Shader& getShader() const { return this->pr_Shader; };

				inline const buffers::VertexArray* getVAO() const { return this->pr_VAO; };
				inline const buffers::IndexBuffer* getIBO() const { return this->pr_IBO; };
			};
		}
	}
}