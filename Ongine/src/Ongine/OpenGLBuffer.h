#pragma once
#include "onpch.h"
#include "Base.h"
#include "Buffer.h"
#include <vector>
#include <string>
#include <glad/glad.h>
namespace ON {

	class ON_API OpenGLVertexBuffer : public VertexBuffer {
	public:
		virtual void Create(VertexBufferSpecification spec, BufferLayout layout) override;
		virtual void Bind() override;
		virtual void LinkAttributes() override;
		virtual void Unbind() override;
		unsigned int GetRenderID();
	private:
		float* vertices;
		uint32_t size;
		unsigned int u_RendererID;
		BufferLayout layout;
	};

	class ON_API OpenGLIndexBuffer : public IndexBuffer {
	public:
		virtual void Create(IndexBufferSpecification spec) override;
		virtual void Bind() override;
		virtual void LinkAttributes() override;
		virtual void Unbind() override;
		unsigned int GetRenderID();
	private:
		unsigned int* indices;
		uint32_t size;
		unsigned int u_RendererID;
	};

	class ON_API OpenGLFramebuffer : Framebuffer{
	public:
		virtual void Create(FramebufferSpecification spec) override;
		virtual void Bind() override;
		virtual void Unbind() override;
		unsigned int GetTCB();
	public:
		unsigned int u_RendererID;
		unsigned int RBO;
		unsigned int TCB;
		int width;
		int height;
	};
}