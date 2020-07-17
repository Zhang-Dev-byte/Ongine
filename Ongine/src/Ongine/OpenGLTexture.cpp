#include "OpenGLTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void ON::OpenGLTexture::Create(TextureSpecification spec)
{
	data = stbi_load(spec.path.c_str(), &width, &height, &comp, 4);

	glGenTextures(1, &u_RendererID);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

void ON::OpenGLTexture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, u_RendererID);
}

void ON::OpenGLTexture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int ON::OpenGLTexture::GetRendererID()
{
	return u_RendererID;
}
