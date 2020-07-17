#pragma once
#include "onpch.h"
#include "Base.h"
#include <vector>
#include <string>
namespace ON {
	struct VertexBufferSpecification {
		float* vertices;
		uint32_t size;
	};
	struct Attributte {
		unsigned int index;
		unsigned int dimension;
		unsigned int offset;
		unsigned int linelength;
	};
	struct BufferLayout {
		std::vector<Attributte> attributes;
	};
	class VertexBuffer {
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

	struct IndexBufferSpecification {
		unsigned int* indices;
		uint32_t size;
	};
	class IndexBuffer {
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
}