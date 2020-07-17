#pragma once

namespace ON {
	class VertexArray {
	public:
		virtual void Create() = 0;
		virtual void Unbind() = 0;
		virtual void Bind() = 0;
	private:
		unsigned int u_RendererID;
	};
}