#include "OpenGLRenderer.h"

void ON::OpenGLRenderer::Draw(OpenGLDrawData data)
{
	data.shader.Use();
	data.VAO.Bind();
	glDrawArrays(GL_TRIANGLES, 0, data.vertices);
}

void ON::OpenGLRenderer::DrawIndexed(OpenGLIndexedDrawData data)
{
	data.shader.Use();
	data.VAO.Bind();
	data.EBO.Bind();
	glDrawElements(GL_TRIANGLES, data.indices, GL_UNSIGNED_INT, 0);
}
