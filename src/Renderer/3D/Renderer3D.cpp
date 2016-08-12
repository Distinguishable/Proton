#include "Renderer3D.h"

namespace proton {
	namespace base {
		namespace renderer {
			Batch::Batch() {
				init();
			}

			Batch::~Batch() {
				delete pr_IBO;
				glDeleteBuffers(1, &pr_VBO);
			}

			void Batch::init() {
				glGenVertexArrays(1, &pr_VAO);
				glGenBuffers(1, &pr_VBO);

				glBindVertexArray(pr_VAO);
				glBindBuffer(GL_ARRAY_BUFFER, pr_VBO);
				glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

				glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
				glEnableVertexAttribArray(SHADER_UV_INDEX);
				glEnableVertexAttribArray(SHADER_NORMAL_INDEX);

				glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
				glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
				glVertexAttribPointer(SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GL_FLOAT)));
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			void Batch::indexInit(const Model* renderable) {
				std::vector<unsigned short> indices = renderable->getIndices();

				pr_IBO = new buffers::IndexBuffer(indices, RENDERER_INDICIES_SIZE);
			}

			void Batch::unbindVAO() {
				glBindVertexArray(0);
			}

			void Batch::flush() {
				glBindVertexArray(pr_VAO);
				pr_IBO->bind();

				glDrawElements(GL_TRIANGLES, 128, GL_UNSIGNED_SHORT, NULL);

				pr_IBO->unbind();
				glBindVertexArray(0);

				indexCount = 0;
			}

			void Batch::begin() {
				glBindBuffer(GL_ARRAY_BUFFER, pr_VBO);
				pr_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			}

			void Batch::submit(const Model* renderable) {
				std::vector<glm::vec3> vertices = renderable->getVertices();
				std::vector<glm::vec2> texCoords = renderable->getTexCoords();
				std::vector<glm::vec3> normals = renderable->getNormals();

				for (int i = 0; i < vertices.size(); i++) {
					pr_Buffer->vertex = vertices.at(i);
					pr_Buffer->uv = texCoords.at(i);
					pr_Buffer->normal = normals.at(i);
					pr_Buffer++;
				}

				indexCount += 6;
			}

			void Batch::end() {
				glUnmapBuffer(GL_ARRAY_BUFFER);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		}
	}
}