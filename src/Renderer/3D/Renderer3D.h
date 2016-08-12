#pragma once

#include "../Model/Model.h"
#include <deque>
#include <glm\gtc\matrix_transform.hpp>

namespace proton {
	namespace base {
		namespace renderer {
#define RENDERER_MAX_SPRITES		10000
#define RENDERER_VERTEX_SIZE		sizeof(VertexData)
#define RENDERER_SPRITE_SIZE		RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE		RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICIES_SIZE		RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_NORMAL_INDEX 2

			class Batch {
			private:
				GLuint pr_VAO;
				GLuint pr_VBO;
				VertexData* pr_Buffer;
				buffers::IndexBuffer* pr_IBO;
				GLsizei indexCount;
			public:
				Batch();
				~Batch();

				void begin();
				void submit(const Model* renderable);
				void end();
				void flush();
				void init();
				void indexInit(const Model* renderable);
				void unbindVAO();
			};
		}
	}
}
