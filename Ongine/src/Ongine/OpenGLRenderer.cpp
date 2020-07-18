#include "OpenGLRenderer.h"
#include "GLErr.h"

void ON::OpenGLRenderer::Draw(OpenGLDrawData data)
{
	data.shader.Use();
	data.VAO.Bind();
	glCall(glDrawArrays(GL_TRIANGLES, 0, data.vertices));
}

void ON::OpenGLRenderer::DrawIndexed(OpenGLIndexedDrawData data)
{
	data.shader.Use();
	data.VAO.Bind();
	data.EBO.Bind();
	glCall(glDrawElements(GL_TRIANGLES, data.indices, GL_UNSIGNED_INT, 0));
}
