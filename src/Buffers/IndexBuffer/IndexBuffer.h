#pragma once

#include <GL\glew.h>
#include <vector>

namespace proton {
	namespace base {
		namespace buffers {
			class IndexBuffer {
			private:
				GLuint pr_BufferID;
				GLuint pr_Count;
			public:

				IndexBuffer(GLushort* data, GLsizei count);
				IndexBuffer(GLushort data, GLsizei count);
				IndexBuffer(std::vector<unsigned short>  data, GLsizei count);

				void bind() const;
				void unbind() const;

				inline const GLuint getBufferID() const { return pr_BufferID; }
				inline const GLuint getCount() const { return pr_Count; }
			};
		}
	}
}
