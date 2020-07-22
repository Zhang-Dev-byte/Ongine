#pragma once
#include <Ongine.h>
namespace FileUtil {
	std::string OpenFilename(char* filter = "All Files (*.*)\0*.*\0", HWND owner = NULL) {
		OPENFILENAME ofn;
		char fileName[MAX_PATH] = "";
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = owner;
		ofn.lpstrFilter = filter;
		ofn.lpstrFile = fileName;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
		ofn.lpstrDefExt = "";
		std::string fileNameStr;
		if (GetOpenFileName(&ofn))
			fileNameStr = fileName;
		return fileNameStr;
	}
}
namespace Dockspace {
	void Begin() {
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
	}
	void End() {
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::PopStyleVar();
		ImGui::End();
	}
}
class EditorLayer : public ON::Layer {
public:
	ON::Camera camera = ON::Camera(-1.6f, 1.6f, -0.9f, 0.9f);
	ON::Sprite sprite = ON::Sprite("res/image.png");
	ON::Scene s;
	ON::Entity c = ON::Entity({ "Camera" }, s.GetRegistry());
	ON::OpenGLFramebuffer FBO;
	entt::entity sentity = s.GetRegistry().create();
	char* name = new char(2048);
	char* path = new char(2048);
	virtual void OnRun() override {
		c.AddComponent<ON::Camera>(camera, s.GetRegistry());
		c.RemoveComponent<ON::Transform>(s.GetRegistry());

		s.SetCamera(&c);
		FBO.Create({ 1280, 720 * 2 });
	}
	virtual void OnUpdate(ON::Input& input) override {
	}
	virtual void OnRender() override {
		FBO.Bind();

		glEnable(GL_TEXTURE_2D);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_FRAMEBUFFER);

		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		s.Render();
		FBO.Unbind();

		Dockspace::Begin();
		ImGui::Begin("Explorer");
		ImGui::InputText("Name", name, 2048);
		if (ImGui::Button("New Entity", ImVec2(100, 20))) {
			ON::Entity ent = ON::Entity({ name }, s.GetRegistry());
		}
		ImGui::End();

		ImGui::Begin("Viewport");
		ImGui::Image((void*)FBO.GetTCB(), ImVec2(1280 / 1.5, 720 / 1.5), ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();

		ImGui::Begin("Control");
		auto view = s.GetRegistry().view<ON::EntityInfo>();
		for (auto e : view) {
			if (ImGui::Button(s.GetRegistry().get<ON::EntityInfo>(e).name.c_str(), ImVec2(100, 20))) {
				sentity = e;
			}
		}
		ImGui::End();

		ImGui::Begin("Console");
		ImGui::End();

		ImGui::Begin("Properties");
		if (s.GetRegistry().has<ON::EntityInfo>(sentity)) {
			ImGui::Text(s.GetRegistry().get<ON::EntityInfo>(sentity).name.c_str());
			if (s.GetRegistry().has<ON::Transform>(sentity)) {
				if (ImGui::TreeNode("Transform")) {
					// Entity
					ImGui::DragFloat2("Position", glm::value_ptr(s.GetRegistry().get<ON::Transform>(sentity).GetPosition()), 0.01f);
					ImGui::DragFloat2("Scale", glm::value_ptr(s.GetRegistry().get<ON::Transform>(sentity).GetScale()));

					//Rotation Code Sorry this is kindof messy
					float rot = (s.GetRegistry().get<ON::Transform>(sentity).GetRotation());
					ImGui::DragFloat("Rotation", &rot);
					s.GetRegistry().get<ON::Transform>(sentity).SetRotation(rot);

					ImGui::TreePop();
				}
			}
			else if (s.GetRegistry().has<ON::Camera>(sentity)) {
				if (ImGui::TreeNode("Camera")) {
					// Camera
					ImGui::DragFloat2("Position", glm::value_ptr(s.GetRegistry().get<ON::Camera>(sentity).GetPosition()), 0.01f);

					//Rotation Code Sorry this is kindof messy
					float rot = (s.GetRegistry().get<ON::Camera>(sentity).GetRotation());
					ImGui::DragFloat("Rotation", &rot);
					s.GetRegistry().get<ON::Camera>(sentity).SetRotation(rot);

					ImGui::TreePop();
				}
			}
			else {
				// Invalid
				ON_CORE_ERROR("Invalid Entity!");
			}
			if (ImGui::TreeNode("Components")) {
				if (ImGui::TreeNode("Sprite")) {
					ImGui::InputText("Path", path, 2048);
					if (ImGui::Button("Add", ImVec2(100, 20))) {
						s.GetRegistry().emplace_or_replace<ON::Sprite>(sentity, ON::Sprite(path));
					}
					ImGui::TreePop();
				}
				ImGui::TreePop();
			}
		}
		ImGui::End();

		Dockspace::End();
	}
};