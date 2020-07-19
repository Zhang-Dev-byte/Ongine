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
	struct OpenGLDrawData {
		uint32_t vertices;
		OpenGLVertexArray VAO;
		OpenGLShader shader;
	};
	struct OpenGLIndexedDrawData {
		uint32_t indices;
		OpenGLIndexBuffer EBO;
		OpenGLVertexArray VAO;
		OpenGLShader shader;
	};
	class OpenGLRenderer{
	public:
		OpenGLRenderer() = default;
		static void Draw(OpenGLDrawData data);
		static void DrawIndexed(OpenGLIndexedDrawData data);
	};
}