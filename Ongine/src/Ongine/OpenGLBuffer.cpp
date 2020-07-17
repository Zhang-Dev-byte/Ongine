#include "OpenGLBuffer.h"
#include "GLErr.h"

void ON::OpenGLVertexBuffer::Create(VertexBufferSpecification spec, BufferLayout layout)
{
	vertices = spec.vertices;
	size = spec.size;
	this->layout = layout;

	glCall( glGenBuffers(1, &u_RendererID) );
}

void ON::OpenGLVertexBuffer::Bind()
{
	glCall( glBindBuffer(GL_ARRAY_BUFFER, u_RendererID) );
}

void ON::OpenGLVertexBuffer::LinkAttributes()
{
	glCall( glBindBuffer(GL_ARRAY_BUFFER, u_RendererID) );
	glCall( glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW) );

	for (auto i = layout.attributes.begin(); i != layout.attributes.end(); i++) {
		Attributte a = *i;
		glCall( glVertexAttribPointer(a.index, a.dimension, GL_FLOAT, GL_FALSE, a.linelength * sizeof(float), (void*)a.offset) );
		glCall( glEnableVertexAttribArray(a.index) );
	}
}

void ON::OpenGLVertexBuffer::Unbind()
{
	glCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
}

void ON::OpenGLIndexBuffer::Create(IndexBufferSpecification spec)
{
	indices = spec.indices;
	size = spec.size;

	glCall( glGenBuffers(1, &u_RendererID) );
}

void ON::OpenGLIndexBuffer::Bind()
{
	glCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, u_RendererID) );
}

void ON::OpenGLIndexBuffer::LinkAttributes()
{
	glCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, u_RendererID) );
	glCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW) );
}

void ON::OpenGLIndexBuffer::Unbind()
{
	glCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
}
