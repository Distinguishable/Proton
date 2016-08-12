#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "../Camera/Camera.h"

namespace proton {
	namespace base {
	
		class ViewMatrix {
			static glm::mat4 CreateViewMatrix(camera::Camera cam) {
				glm::mat4 viewMatrix(1.0);
				glm::rotate(viewMatrix, glm::radians(cam.getPitch()), glm::vec3(1, 0, 0));
				glm::rotate(viewMatrix, glm::radians(cam.getYaw()), glm::vec3(0, 1, 0));
				glm::vec3 cameraPos = cam.getPosition();
				glm::vec3 negativeCamPos = glm::vec3(-cameraPos.x, -cameraPos.y, -cameraPos.z);
				glm::translate(viewMatrix, negativeCamPos);
				return viewMatrix;
			}
		};
	
	}
}