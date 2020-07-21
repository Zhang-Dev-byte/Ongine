#pragma once
#include "Base.h"

namespace ON {
	class ON_API VertexArray {
	public:
		virtual void Create() = 0;
		virtual void Unbind() = 0;
		virtual void Bind() = 0;
	private:
		unsigned int u_RendererID;
	};
}