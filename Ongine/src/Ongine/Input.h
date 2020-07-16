#pragma once
#include "onpch.h"
#include "Application.h"
#include "Log.h"
#include "Instumentor.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace ON {
	class Input {
	public:
		Input(GLFWwindow* window);
		bool GetKey(int key);
	private:
		GLFWwindow* window;
	};
}