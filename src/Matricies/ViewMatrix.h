#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "../Camera/Camera.h"

namespace proton {
	namespace base {
	
		class ViewMatrix {
		public:
			static glm::mat4 CreateViewMatrix(camera::Camera cam) {
				glm::mat4 viewMatrix(1.0);
				glm::rotate(viewMatrix, glm::radians(cam.getPitch()), glm::vec3(1, 0, 0));
				glm::rotate(viewMatrix, glm::radians(cam.getYaw()), glm::vec3(0, 1, 0));
				glm::vec3 cameraPos = cam.getPosition();
				glm::vec3 negativeCamPos = glm::vec3(-cameraPos.x, -cameraPos.y, -cameraPos.z);
				glm::translate(viewMatrix, negativeCamPos);
				return viewMatrix;
			}

			static glm::mat4 LookAt(glm::vec3  const & eye, glm::vec3  const & center, glm::vec3  const & up)
			{
				glm::vec3  f = glm::normalize(center - eye);
				glm::vec3  u = glm::normalize(up);
				glm::vec3  s = glm::normalize(cross(f, u));
				u = glm::cross(s, f);

				glm::mat4 Result(1);
				Result[0][0] = s.x;
				Result[1][0] = s.y;
				Result[2][0] = s.z;
				Result[0][1] = u.x;
				Result[1][1] = u.y;
				Result[2][1] = u.z;
				Result[0][2] = -f.x;
				Result[1][2] = -f.y;
				Result[2][2] = -f.z;
				Result[3][0] = -glm::dot(s, eye);
				Result[3][1] = -glm::dot(u, eye);
				Result[3][2] = glm::dot(f, eye);
				return Result;
			}
		};
	
	}
}