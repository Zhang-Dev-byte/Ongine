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

	app->OnRun();


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

	while (!glfwWindowShouldClose(window))
	{
		app->OnUpdate(input);

		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();

		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		app->OnRender();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();

	glfwTerminate();
	delete app;
}