#pragma once
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

namespace GE {
	class TriangleRenderer {
	public: 
		TriangleRenderer();
		virtual ~TriangleRenderer();
		void init();
		void update();
		void draw();
		void destroy();
		void displayShaderCompilerError(GLuint shaderId);
	private: 
		GLuint programId, vboTriangle;
		GLint vertexPos2DLocation;
	};
}