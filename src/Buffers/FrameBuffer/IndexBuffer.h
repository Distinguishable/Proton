#pragma once

#include <iostream>
#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>

#include "../VertexBuffer/VertexBuffer.h"

namespace proton {
	namespace base {
		namespace buffers {
			class IndexBuffer {
			private:
				GLuint pr_BufferID;
				GLuint pr_Count;
			public:

				IndexBuffer(std::vector<GLushort*> data, GLsizei count);

				void bind() const;
				void unbind() const;

				inline const GLuint getBufferID() const { return pr_BufferID; }
				inline const GLuint getCount() const { return pr_Count; }
			};
		}
	}
}