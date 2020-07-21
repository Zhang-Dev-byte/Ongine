#pragma once
#include "onpch.h"
#include "Base.h"
#include <vector>
#include <string>
namespace ON {
	struct ON_API VertexBufferSpecification {
		float* vertices;
		uint32_t size;
	};
	struct ON_API Attributte {
		unsigned int index;
		unsigned int dimension;
		unsigned int offset;
		unsigned int linelength;
	};
	struct ON_API BufferLayout {
		std::vector<Attributte> attributes;
	};
	class ON_API VertexBuffer {
	public:
		virtual void Create(VertexBufferSpecification spec, BufferLayout layout) = 0;
		virtual void Bind() = 0;
		virtual void LinkAttributes() = 0;
		virtual void Unbind() = 0;
	private:
		float* vertices;
		uint32_t size;
		unsigned int u_RendererID;
	};

	struct ON_API IndexBufferSpecification {
		unsigned int* indices;
		uint32_t size;
	};
	class ON_API IndexBuffer {
	public:
		virtual void Create(IndexBufferSpecification spec) = 0;
		virtual void Bind() = 0;
		virtual void LinkAttributes() = 0;
		virtual void Unbind() = 0;
	private:
		unsigned int* indices;
		uint32_t size;
		unsigned int u_RendererID;
	};

	struct ON_API FramebufferSpecification {
		int width;
		int height;
	};
	class ON_API Framebuffer {
	public:
		virtual void Create(FramebufferSpecification spec) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};
}