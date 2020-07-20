#pragma once
#include "onpch.h"
#include "Base.h"
#include <vector>
#include <string>
#include <glad/glad.h>
#include "OpenGLVertexArray.h"
#include "OpenGLBuffer.h"
#include "OpenGLShader.h"
#include "OpenGLRenderer.h"
#include "Texture.h"
#include "OpenGLTexture.h"
#include "Camera.h"
#include "Transform.h"

namespace ON {
	class Sprite {
	public:
		Sprite(const std::string& path);
		void Render(ON::Camera camera, ON::Transform transform);
	private:
		ON::OpenGLShader shader;
		ON::OpenGLIndexBuffer EBO;
		ON::OpenGLVertexBuffer VBO;
		ON::OpenGLVertexArray VAO;
		ON::OpenGLTexture texture;

		float vertices[5 * 4] = {
			 0.07f,  0.07f, 0.0f,   1.0f, 1.0f,
			 0.07f, -0.07f, 0.0f,   1.0f, 0.0f,
			-0.07f, -0.07f, 0.0f,   0.0f, 0.0f,
			-0.07f,  0.07f, 0.0f,   0.0f, 1.0f
		};
		unsigned int indices[3 * 2] = {
			0, 1, 3,
			1, 2, 3
		};
	};
}
