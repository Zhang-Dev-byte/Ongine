#include "GLErr.h"

void glClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool glCheckError()
{
	while (GLenum e = glGetError()) {
		std::stringstream er;
		er << (std::string)"0x" << std::hex << e;
		ON_CORE_CRITICAL("[OpenGL Error!]{0} \n@line: {1} : {2}", er.str(), __LINE__, __FILE__);
		return false;
	}
	return true;
}
