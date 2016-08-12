#pragma once

#include <vector>
#include <GL\glew.h>

#include "../VertexBuffer/VertexBuffer.h"

namespace proton {
	namespace base {
		namespace buffers {
			class VertexArray {
			private:
				GLuint pr_ArrayID;
				std::vector<Buffer*> pr_Buffers;
			public:
				VertexArray();
				~VertexArray();

				void addBuffer(Buffer* buffer, GLuint index);

				void bind() const;
				void unbind() const;
			};
		}
	}
}
