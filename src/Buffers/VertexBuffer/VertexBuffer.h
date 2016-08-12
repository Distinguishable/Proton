#pragma once

#include <GL\glew.h>
#include <vector>
#include <glm\glm.hpp>

namespace proton {
	namespace base {
		namespace buffers {
			class Buffer {
			private:
				GLuint pr_BufferID;
				GLuint pr_ComponentCount;
			public:

				Buffer(std::vector<glm::vec3> data, GLsizei count, GLuint componentCount);
				Buffer(std::vector<glm::vec2> data, GLsizei count, GLuint componentCount);

				void bind() const;
				void unbind() const;

				inline GLuint getBufferID() { return pr_BufferID; }
				inline GLuint getCount() { return pr_ComponentCount; }
			};
		}
	}
}