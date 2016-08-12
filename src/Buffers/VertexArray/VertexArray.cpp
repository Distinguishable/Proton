#include "VertexArray.h"

namespace proton {
	namespace base {
		namespace buffers {

			VertexArray::VertexArray() {
				glGenVertexArrays(1, &pr_ArrayID);
			}

			VertexArray::~VertexArray() {
				for (int i = 0; i < pr_Buffers.size(); i++) {
					delete pr_Buffers[i];
				}
			}

			void VertexArray::addBuffer(Buffer* buffer, GLuint index) {
				bind();
				buffer->bind();

				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, buffer->getCount(), GL_FLOAT, GL_FALSE, 0, 0);

				buffer->unbind();
				unbind();
			}

			void VertexArray::bind() const {
				glBindVertexArray(pr_ArrayID);
			}

			void VertexArray::unbind() const {
				glBindVertexArray(0);
			}
		}
	}
}