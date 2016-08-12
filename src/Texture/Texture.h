#pragma once

#include <GL\glew.h>
#include <iostream>

namespace proton {
	namespace base {
		namespace renderer {
			class Texture {
			public:
				static GLuint loadBMP_custom(const char * imagepath);
			};
		}
	}
}