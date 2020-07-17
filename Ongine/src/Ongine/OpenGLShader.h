#pragma once
#include "Shader.h"
#include "Log.h"

namespace ON {
	class OpenGLShader : public Shader {
	public:
		virtual void Create(ShaderSpecification spec) override;
		virtual void Use() override;
        inline void SetInt(const std::string& name, int value) {
            glUniform1i(glGetUniformLocation(u_RendererID, name.c_str()), value);
        }
	private:
        void CheckCompilerErrors(unsigned int shader, std::string type) {
            int success;
            char infoLog[1024];
            if (type != "PROGRAM")
            {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    ON_CORE_CRITICAL("Shader compilation error of type: {0}\n{1}\n -- --------------------------------------------------- -- ", type, infoLog);
                }
            }
            else
            {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                    ON_CORE_CRITICAL("Program linking error of type: {0}\n{1}\n -- --------------------------------------------------- -- ", type, infoLog);
                }
            }
        }
		unsigned int u_RendererID;
	};
}