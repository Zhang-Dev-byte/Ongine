#include "Sprite.h"

ON::Sprite::Sprite(const std::string& path)
{
	shader.Create({ "res/sysshaders/vs.shader", "res/sysshaders/fs.shader" });
	std::vector<ON::Attributte> dest;
	dest.push_back({ 0, 3, 0, 5 });
	dest.push_back({ 1, 2, (3 * sizeof(float)), 5 });

	ON::BufferLayout layout = { dest };

	VAO.Create();
	VBO.Create({ vertices, sizeof(vertices) }, layout);
	EBO.Create({ indices, sizeof(indices) });

	VAO.Bind();

	EBO.LinkAttributes();

	VBO.LinkAttributes();

	VBO.Unbind();
	VAO.Unbind();

	texture.Create({ path });
	texture.Bind();

	/*shader.Use();
	shader.SetInt("diffuse", texture.GetRendererID());*/
}

void ON::Sprite::Render(ON::Camera camera, ON::Transform transform)
{
	shader.Use();
	shader.SetMatrix4f("model", transform.GetModelMatrix());
	shader.SetMatrix4f("vp", camera.GetViewProjection());
	shader.SetInt("diffuse", texture.GetRendererID());

	OpenGLRenderer::DrawIndexed({ (sizeof(indices) / sizeof(indices[0])), EBO, VAO, shader });
}