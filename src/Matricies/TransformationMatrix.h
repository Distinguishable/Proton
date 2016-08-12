#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace proton {
	namespace base {
		class TransformationMatrix {
		public:
			static glm::mat4 CreateTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale) {
				glm::mat4 matrix(1.0);
				glm::translate(matrix, translation);
				glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
				glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
				glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
				glm::scale(matrix, glm::vec3(scale.x, scale.y, scale.z));
				return matrix;
			}
		};
	}
}