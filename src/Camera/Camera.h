#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <GLFW\glfw3.h>

namespace proton {
	namespace base {
		namespace camera {
			class Camera {
			public:
				glm::vec3 pr_Position;
				float pr_Pitch;
				float pr_Yaw;
				float pr_Roll;

				Camera(glm::vec3 position) {
					this->pr_Position = position;
				}

				void move(GLFWwindow* window) {
					if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
						pr_Position.z -= 0.02f;
					}

					if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
						pr_Position.z += 0.02f;
					}

					if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
						pr_Position.x -= 0.02f;
					}

					if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
						pr_Position.x += 0.02f;
					}
				}

				glm::vec3 getPosition() {
					return pr_Position;
				}

				float getPitch() {
					return pr_Pitch;
				}

				float getYaw() {
					return pr_Yaw;
				}

				float getRoll() {
					return pr_Roll;
				}
			};
		}
	}
}