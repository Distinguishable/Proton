#include "Window.h"

namespace proton {
	namespace base {
		namespace window {
			Window::Window(int width, int height, const char* title) {
				this->pr_Width = width;
				this->pr_Height = height;
				this->pr_Title = title;
				if (!this->Init()) {
					std::cout << "Could not init GLFW" << std::endl;
					glfwTerminate();
				}
			}

			Window::~Window() {
				
			}

			bool Window::Init() {
				if (!glfwInit())
				{
					std::cout << "Could not Initilize the GLFW" << std::endl;
					return false;
				}

				
				glfwWindowHint(GLFW_SAMPLES, 2); 
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
				

				this->pr_Window = glfwCreateWindow(this->pr_Width, this->pr_Height, this->pr_Title, NULL, NULL);
				
				if (this->pr_Window == NULL) {
					std::cout << "Could not Initilize the window" << std::endl;
					return false;
				}

				glfwMakeContextCurrent(this->pr_Window);
				glewExperimental = true;

				if (glewInit() != GLEW_OK) {
					std::cout << "Could not Initilize GLEW" << std::endl;
					return false;
				}

				return true;
			}

			void Window::Update() {
				glfwSwapBuffers(this->pr_Window);
				glfwPollEvents();
			}

			void Window::Clear() {
				glEnable(GL_DEPTH_TEST);
				glEnable(GL_CULL_FACE);
				glClearColor(0.2f, 0.3f, 0.9f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glCullFace(GL_BACK);
			}

			bool Window::WindowShouldClose() {
				return glfwWindowShouldClose(this->pr_Window);
			}
		}
	}
}