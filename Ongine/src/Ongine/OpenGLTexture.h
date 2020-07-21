#pragma once
#include "onpch.h"
#include "Base.h"
#include "Texture.h"
#include <vector>
#include <string>
#include <glad/glad.h>
namespace ON {
	class ON_API OpenGLTexture : Texture{
	public:
		virtual void Create(TextureSpecification spec) override;
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual unsigned int GetRendererID() override;
	private:
		unsigned char* data;
		unsigned int u_RendererID;
		int width;
		int height;
		int comp;
	};
}