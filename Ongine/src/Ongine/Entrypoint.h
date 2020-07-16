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
	extern Application* CreateApplication();
	extern void ResizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
}
int main(int argc, char* argv[]) {
	ON::Log::Init();

	auto app = ON::CreateApplication();

	if (!glfwInit()) {
		ON_CORE_CRITICAL("Failed to initalize GLFW");
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	app->OnRun();

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Ongine", NULL, NULL);
	ON::Input input(window);
	if (window == NULL)
	{
		ON_CORE_CRITICAL("Failed to initalize Window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, ON::ResizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		ON_CORE_CRITICAL("Failed to initalize Glad");
		return -1;
	}

	while (!glfwWindowShouldClose(window))
	{
		app->OnUpdate(input);

		glClear(GL_COLOR_BUFFER_BIT);

		app->OnRender();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	delete app;
}