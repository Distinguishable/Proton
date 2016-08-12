#pragma once

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace proton {
	namespace base {
		namespace window {
			class Window {
			public:
				Window(int width, int height, const char* title);
				~Window();

				bool WindowShouldClose();
				bool Init();
				
				void Update();
				void Clear();

				inline GLFWwindow* getWindow() const { return this->pr_Window; }
			private:
				int pr_Width;
				int pr_Height;
				const char* pr_Title;

				GLFWwindow* pr_Window;
			};
		}
	}
}