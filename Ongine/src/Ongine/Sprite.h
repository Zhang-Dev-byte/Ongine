#pragma once
#include "Base.h"
#include "Application.h"
#include "Log.h"
#include "Instumentor.h"
#include "Input.h"
#include "Entrypoint.h"
#include "Shader.h"
#include "OpenGLShader.h"
#include "Buffer.h"
#include "OpenGLBuffer.h"
#include "VertexArray.h"
#include "OpenGLVertexArray.h"
#include "OpenGLRenderer.h"
#include "Texture.h"
#include "OpenGLTexture.h"
#include "Transform.h"
#include "Camera.h"
#include "Core.h"

namespace ON {
	class Sprite {
	public:
		Sprite(const std::string& path);
		void Render(ON::Camera camera);
	public:
		ON::Transform transform = ON::Transform();
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

ON::Sprite::Sprite(const std::string& path)
{
	shader.Create({ "res/sysshaders/vs.shader", "res/sysshaders/fs.shader" });
	std::vector<ON::Attributte> dest;
	dest.push_back({ 0, 3, 0, 5 });
	dest.push_back({ 1, 2, (3 * sizeof(float)), 5 });

	ON::BufferLayout layout = { dest };

	VAO.Create();
	VBO.Create({ vertices, sizeof(vertices) }, layout);
	EBO.Create({ indices, sizeof(indices) });

	VAO.Bind();

	EBO.LinkAttributes();

	VBO.LinkAttributes();

	VBO.Unbind();
	VAO.Unbind();

	texture.Create({ path });
	texture.Bind();

	shader.Use();
	shader.SetInt("diffuse", texture.GetRendererID());
}

void ON::Sprite::Render(ON::Camera camera)
{
	shader.Use();
	shader.SetMatrix4f("model", transform.GetModelMatrix());
	shader.SetMatrix4f("view", camera.GetViewMatrix());
	shader.SetMatrix4f("projection", camera.GetProjectionMatrix());
	renderer.DrawIndexed({ (sizeof(indices) / sizeof(indices[0])), EBO, VAO, shader });
}