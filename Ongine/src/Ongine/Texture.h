#pragma once
#include <string>
namespace ON {
	struct TextureSpecification {
		std::string path;
	};
	class Texture {
	public:
		virtual void Create(TextureSpecification spec) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual unsigned int GetRendererID() = 0;
	private:
		unsigned int u_RendererID;
		int width;
		int height;
	};
}