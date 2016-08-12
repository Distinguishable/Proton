#pragma once

#include <GL\glew.h>
#include <vector>
#include <map>
#include <string>

#include "../Renderer/Model/Model.h"

namespace proton {
	namespace base {
		namespace renderer {
			class OBJLoader {
			public:
				static Model LoadOBJ(const char* filePath, glm::vec3 position, shader::Shader& shader);
			};
		}
	}
}