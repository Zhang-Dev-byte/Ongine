#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace ON {
	struct ShaderSpecification {
		std::string vertexPath;
		std::string fragmentPath;
	};
	class Shader {
	public:
		virtual void Create(ShaderSpecification spec) = 0;
		virtual void Use() = 0;
	private:
		unsigned int u_RendererID;
	};
}