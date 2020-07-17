#pragma once
#include "onpch.h"
#include "Base.h"
#include "VertexArray.h"
#include <vector>
#include <string>
#include <glad/glad.h>

namespace ON {
	class OpenGLVertexArray : public VertexArray{
	public:
		virtual void Create() override;
		virtual void Unbind() override;
		virtual void Bind() override;
	private:
		unsigned int u_RendererID;
	};
}