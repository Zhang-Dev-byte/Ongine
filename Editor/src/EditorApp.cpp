#include <Ongine.h>
#include "EditorLayer.h"

class EditorApp : public ON::Application {
public:
	ON::Camera camera = ON::Camera(-1.6f, 1.6f, -0.9f, 0.9f);
	ON::Sprite sprite = ON::Sprite("res/image.png");
	ON::Scene s;
	ON::Entity e = ON::Entity({"Entity"}, s.GetRegistry());
	ON::Entity c = ON::Entity({"Camera"}, s.GetRegistry());
	ON::OpenGLFramebuffer FBO;

	virtual void OnRun() override {
		FBO.Create({ 1280, 720 });
		e.AddComponent<ON::Sprite>(sprite, s.GetRegistry());
		c.AddComponent<ON::Camera>(camera, s.GetRegistry());
		c.RemoveComponent<ON::Transform>(s.GetRegistry());

		s.SetCamera(&c);
	}
	virtual void OnUpdate(ON::Input& input) override {
		
	}
	virtual void OnRender() override {
		FBO.Bind();
		glClear(GL_COLOR_BUFFER_BIT);
		s.Render();
		FBO.Unbind();

		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
		ImGui::Begin("Viewport");
		ImGui::Image((void*)FBO.GetTCB(), ImVec2(1280 / 1.5f, 720 / 1.5f));
		ImGui::End();

		ImGui::Begin("Control");
		ImGui::DragFloat2("Position", glm::value_ptr(e.GetComponent<ON::Transform>(s.GetRegistry()).GetPosition()), 0.01f);
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::PopStyleVar();
		ImGui::End();
	}
};

ON::Application* ON::CreateApplication() {
	return new EditorApp();
}

void ON::OnLayersCreate() {
	ON::LayerStack::PushLayer(new EditorLayer());
}