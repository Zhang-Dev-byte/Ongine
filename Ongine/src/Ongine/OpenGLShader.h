#pragma once
#include "Base.h"
#include "Shader.h"
#include "Log.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ON {
	class ON_API OpenGLShader : public Shader {
	public:
		virtual void Create(ShaderSpecification spec) override;
		virtual void Use() override;
        inline void SetInt(const std::string& name, int value) {
            glUniform1i(glGetUniformLocation(u_RendererID, name.c_str()), value);
        }
        inline void SetMatrix4f(const std::string& name, glm::mat4& value) {
            glUniformMatrix4fv(glGetUniformLocation(u_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
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