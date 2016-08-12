#include "VertexBuffer.h"
#include <iostream>

namespace proton {
	namespace base {
		namespace buffers {
			Buffer::Buffer(std::vector<glm::vec3> data, GLsizei count, GLuint componentCount) : pr_ComponentCount(componentCount) {
				glGenBuffers(1, &pr_BufferID);
				glBindBuffer(GL_ARRAY_BUFFER, pr_BufferID);
				glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::vec3), &data[0], GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			Buffer::Buffer(std::vector<glm::vec2> data, GLsizei count, GLuint componentCount) : pr_ComponentCount(componentCount) {
				glGenBuffers(1, &pr_BufferID);
				glBindBuffer(GL_ARRAY_BUFFER, pr_BufferID);
				glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::vec2), &data[0], GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			void Buffer::bind() const {
				glBindBuffer(GL_ARRAY_BUFFER, pr_BufferID);
			}

			void Buffer::unbind() const {
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		}
	}
}