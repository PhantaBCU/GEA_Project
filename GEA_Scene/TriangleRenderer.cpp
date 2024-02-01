#include "TriangleRenderer.h"
#include <iostream>
#include "gtc/type_ptr.hpp"

namespace GE {
	struct Vertex {
		float x, y, z;
		float r, g, b, a;
		Vertex(float _x, float _y, float _z, float _r, float _g, float _b, float _a) {
			x = _x;
			y = _y;
			z = _z;

			r = _r;
			g = _g;
			b = _b;
			a = _a;
		}
		Vertex() {
			x = y = z = 0;
			r = g = b = a = 0;
		}
	};
	Vertex vertexData[] = {
		Vertex(- 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
		Vertex(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
		Vertex(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f)
	};
	
	TriangleRenderer::TriangleRenderer() {
		pos.x = pos.y = pos.z = 0.0f;
		rot.x = rot.y = rot.z = 0.0f;
		scl.x = scl.y = scl.z = 1.0f;
		programId = transformUniformId = viewUniformId = projectionUniformId = vboTriangle = 0;
		vertexPos3DLocation = 0;
	}
	
	TriangleRenderer::~TriangleRenderer() {}
	
	void TriangleRenderer::displayShaderCompilerError(GLuint shaderId)
	{
		GLint MsgLen = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &MsgLen);
		if (MsgLen > 1) {
			GLchar* Msg = new GLchar[MsgLen + 1];
			glGetShaderInfoLog(shaderId, MsgLen, NULL, Msg);
			std::cerr << "Error compiling shader" << Msg << std::endl;
			delete[] Msg;
		}
	}

	void TriangleRenderer::init() {
		
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* V_ShaderCode[] = {
			"#version 140\n"
			"in vec3 vertexPos3D;\n"
			"in vec4 vColour;\n"
			"out vec4 fColour;\n"
			"uniform mat4 viewMat;\n"
			"uniform mat4 projMat;\n"
			"uniform mat4 transformMat;\n"
			"void main() {\n"
			"gl_Position = projMat * viewMat * transformMat * vec4(vertexPos3D.x, vertexPos3D.y, vertexPos3D.z, 1);\n"
			"fColour = vColour;\n"
			"}\n" 
		};

		glShaderSource(vertexShader, 1, V_ShaderCode, NULL);
		glCompileShader(vertexShader);
		GLint isShaderCompiledOK = GL_FALSE;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isShaderCompiledOK);
		if (isShaderCompiledOK != GL_TRUE) {
			std::cerr << "Error compiling vertex shader" << std::endl;
			displayShaderCompilerError(vertexShader);
			return;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* F_ShaderCode[] = {
			"#version 140\n"
			"in vec4 fColour;\n"
			"out vec4 fragmentColour;\n"
			"void main() {\n"
			"fragmentColour = fColour;\n"
			"}\n"
		};

		glShaderSource(fragmentShader, 1, F_ShaderCode, NULL);
		glCompileShader(fragmentShader);
		isShaderCompiledOK = GL_FALSE;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isShaderCompiledOK);
		if (isShaderCompiledOK != GL_TRUE) {
			std::cerr << "Error compiling fragment shader" << std::endl;
			displayShaderCompilerError(fragmentShader);
			return;
		}

		programId = glCreateProgram();

		glAttachShader(programId, vertexShader);
		glAttachShader(programId, fragmentShader);

		glLinkProgram(programId);

		GLint isProgramLinked = GL_FALSE;
		glGetProgramiv(programId, GL_LINK_STATUS, &isProgramLinked);
		if (isProgramLinked != GL_TRUE) {
			std::cerr << "Failed to link program!" << std::endl;
		}

		vertexPos3DLocation = glGetAttribLocation(programId, "vertexPos3D");

		if (vertexPos3DLocation == -1) {
			std::cerr << "Problem getting vertexPos3D" << std::endl;
		}

		vertexColourLocation = glGetAttribLocation(programId, "vColour");

		if (vertexColourLocation == -1) {
			std::cerr << "Problem getting vColour" << std::endl;
		}

		viewUniformId = glGetUniformLocation(programId, "viewMat");
		projectionUniformId = glGetUniformLocation(programId, "projMat");
		transformUniformId = glGetUniformLocation(programId, "transformMat");
		
		glGenBuffers(1, &vboTriangle);

		glBindBuffer(GL_ARRAY_BUFFER, vboTriangle);

			glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void TriangleRenderer::update()
	{

	}

	void TriangleRenderer::draw(Camera* cam)
	{

		glm::mat4 transformationMat = glm::mat4(1.0f);

		transformationMat = glm::translate(transformationMat, pos);
		transformationMat = glm::rotate(transformationMat, glm::radians(rot.x), xAxis);
		transformationMat = glm::rotate(transformationMat, glm::radians(rot.y), yAxis);
		transformationMat = glm::rotate(transformationMat, glm::radians(rot.z), zAxis);
		transformationMat = glm::scale(transformationMat, scl);

		glm::mat4 viewMat = cam->getViewMatrix();
		glm::mat4 projectionMat = cam->getProjectionMatrix();

		glUseProgram(programId);

			glUniformMatrix4fv(transformUniformId,	 1, GL_FALSE, glm::value_ptr(transformationMat));
			glUniformMatrix4fv(viewUniformId,		 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(projectionUniformId,	 1, GL_FALSE, glm::value_ptr(projectionMat));
















			glBindBuffer(GL_ARRAY_BUFFER, vboTriangle);

				glEnableVertexAttribArray(vertexPos3DLocation);
				glVertexAttribPointer(vertexPos3DLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, x));

				glEnableVertexAttribArray(vertexColourLocation);
				glVertexAttribPointer(vertexColourLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, r));

				glDrawArrays(GL_TRIANGLES, 0, sizeof(vertexData) / sizeof(Vertex));

				glDisableVertexAttribArray(vertexPos3DLocation);
				glDisableVertexAttribArray(vertexColourLocation);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

		glUseProgram(0);
	}

	void TriangleRenderer::destroy()
	{
		glDeleteProgram(programId);
		glDeleteBuffers(1, &vboTriangle);
	}
}