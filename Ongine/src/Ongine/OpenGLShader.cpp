#include "OpenGLShader.h"

void ON::OpenGLShader::Create(ShaderSpecification spec)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(spec.vertexPath);
        fShaderFile.open(spec.fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        ON_CORE_CRITICAL("Failed to load shader file.");
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckCompilerErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    CheckCompilerErrors(fragment, "FRAGMENT");

    u_RendererID = glCreateProgram();
    glAttachShader(u_RendererID, vertex);
    glAttachShader(u_RendererID, fragment);
    glLinkProgram(u_RendererID);
    CheckCompilerErrors(u_RendererID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void ON::OpenGLShader::Use()
{
    glUseProgram(u_RendererID);
}
