#include "OpenGLVertexArray.h"
#include "GLErr.h"

void ON::OpenGLVertexArray::Create()
{
	glCall( glGenVertexArrays(1, &u_RendererID) );
}

void ON::OpenGLVertexArray::Unbind()
{
	glCall( glBindVertexArray(0) );
}

void ON::OpenGLVertexArray::Bind()
{
	glCall( glBindVertexArray(u_RendererID) );
}

unsigned int ON::OpenGLVertexArray::GetRenderID()
{
	return u_RendererID;
}
