#pragma once
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm.hpp>
#include "Camera.h"

namespace GE {
	class TriangleRenderer {
	public: 
		TriangleRenderer();
		virtual ~TriangleRenderer();
		void init();
		void update();
		void draw(Camera* cam);
		void destroy();

		//Get & Set individual floats

		float getPosX() {return pos.x;}
		float getPosY() {return pos.y;}
		float getPosZ() {return pos.z;}
		float getRotX() {return rot.x;}
		float getRotY() {return rot.y;}
		float getRotZ() {return rot.z;}
		float getSclX() {return scl.x;}
		float getSclY() {return scl.y;}
		float getSclZ() {return scl.z;}

		void setPosX(float val) { pos.x = val; }
		void setPosY(float val) { pos.y = val; }
		void setPosZ(float val) { pos.z = val; }
		void setRotX(float val) { rot.x = val; }
		void setRotY(float val) { rot.y = val; }
		void setRotZ(float val) { rot.z = val; }
		void setSclX(float val) { scl.x = val; }
		void setSclY(float val) { scl.y = val; }
		void setSclZ(float val) { scl.z = val; }

		//Get & Set by vec3

		glm::vec3 getVec3(int type) {
			switch (type) {
			case 1:	return pos;
			case 2:	return rot;
			case 3:	return scl;
			}
		}

		void setVec3(int type, glm::vec3 vec) {
			switch (type) {
			case 1:
				pos = vec;
				break;
			case 2:
				rot = vec;
				break;
			case 3:
				scl = vec;
				break;
			}
		}
		void displayShaderCompilerError(GLuint shaderId);
	
	private: 
		GLuint programId, transformUniformId, viewUniformId, projectionUniformId, vboTriangle;
		GLint vertexPos3DLocation, vertexColourLocation;
		glm::vec3 pos, rot, scl;
		glm::vec3 xAxis = { 1.0f, 0.0f, 0.0f };
		glm::vec3 yAxis = { 0.0f, 1.0f, 0.0f };
		glm::vec3 zAxis = { 0.0f, 0.0f, 1.0f };
	};
}