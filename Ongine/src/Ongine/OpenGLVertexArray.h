#pragma once
#include "onpch.h"
#include "Base.h"
#include "VertexArray.h"
#include <vector>
#include <string>
#include <glad/glad.h>

namespace ON {
	class ON_API OpenGLVertexArray : public VertexArray{
	public:
		virtual void Create() override;
		virtual void Unbind() override;
		virtual void Bind() override;
		unsigned int GetRenderID();
	private:
		unsigned int u_RendererID;
	};
}