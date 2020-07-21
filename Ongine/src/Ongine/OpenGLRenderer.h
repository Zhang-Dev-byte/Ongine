#pragma once
#include "onpch.h"
#include "Base.h"
#include <vector>
#include <string>
#include <glad/glad.h>
#include "OpenGLVertexArray.h"
#include "OpenGLBuffer.h"
#include "OpenGLShader.h"

namespace ON {
	struct ON_API OpenGLDrawData {
		uint32_t vertices;
		OpenGLVertexArray VAO;
		OpenGLShader shader;
	};
	struct ON_API OpenGLIndexedDrawData {
		uint32_t indices;
		OpenGLIndexBuffer EBO;
		OpenGLVertexArray VAO;
		OpenGLShader shader;
	};
	class ON_API OpenGLRenderer{
	public:
		OpenGLRenderer() = default;
		static void Draw(OpenGLDrawData data);
		static void DrawIndexed(OpenGLIndexedDrawData data);
	};
}