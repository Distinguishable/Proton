#include "IndexBuffer.h"

namespace proton {
	namespace base {
		namespace buffers {
			IndexBuffer::IndexBuffer(GLushort* data, GLsizei count) : pr_Count(count) {
				glGenBuffers(1, &pr_BufferID);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pr_BufferID);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), &data[0], GL_STATIC_DRAW);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}

			IndexBuffer::IndexBuffer(GLushort data, GLsizei count) : pr_Count(count) {
				glGenBuffers(1, &pr_BufferID);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pr_BufferID);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), &data, GL_STATIC_DRAW);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}

			IndexBuffer::IndexBuffer(std::vector<unsigned short> data, GLsizei count) : pr_Count(count) {
				glGenBuffers(1, &pr_BufferID);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pr_BufferID);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned short), &data[0], GL_STATIC_DRAW);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}

			void IndexBuffer::bind() const {
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pr_BufferID);
			}

			void IndexBuffer::unbind() const {
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}
		}
	}
}
