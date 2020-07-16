#include "Input.h"

ON::Input::Input(GLFWwindow* window)
{
	this->window = window;
}

bool ON::Input::GetKey(int key)
{
	return (glfwGetKey(window, key) == GLFW_PRESS);
}
