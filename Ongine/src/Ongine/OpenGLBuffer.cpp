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

unsigned int ON::OpenGLVertexBuffer::GetRenderID()
{
	return u_RendererID;
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

unsigned int ON::OpenGLIndexBuffer::GetRenderID()
{
	return u_RendererID;
}

void ON::OpenGLFramebuffer::Create(FramebufferSpecification spec)
{
	width = spec.width;
	height = spec.height;
	glCall( glGenFramebuffers(1, &u_RendererID) );
	glCall( glBindFramebuffer(GL_FRAMEBUFFER, u_RendererID) );

	glCall( glGenTextures(1, &TCB) );
	glCall( glBindTexture(GL_TEXTURE_2D, TCB) );
	glCall( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, spec.width, spec.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL) );
	glCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
	glCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
	glCall( glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TCB, 0) );

	glCall( glGenRenderbuffers(1, &RBO) );
	glCall( glBindRenderbuffer(GL_RENDERBUFFER, RBO) );
	glCall( glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, spec.width, spec.height) );
	glCall( glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO) );

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		ON_CORE_ERROR("Framebuffer is not complete!");
	}

	glCall( glBindFramebuffer(GL_FRAMEBUFFER, 0) );
}

void ON::OpenGLFramebuffer::Bind()
{
	glCall( glBindFramebuffer(GL_FRAMEBUFFER, u_RendererID) );
	glCall( glViewport(0, 0, width, height) );
}

void ON::OpenGLFramebuffer::Unbind()
{
	glCall( glBindFramebuffer(GL_FRAMEBUFFER, 0) );
}

unsigned int ON::OpenGLFramebuffer::GetTCB()
{
	return TCB;
}
