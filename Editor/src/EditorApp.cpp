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
	entt::entity sentity = s.GetRegistry().create();

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

		Dockspace::Begin();

		ImGui::Begin("Viewport");
		ImGui::Image((void*)FBO.GetTCB(), ImVec2(1280 / 1.5f, 720 / 1.5f));
		ImGui::End();

		ImGui::Begin("Control");
		auto view = s.GetRegistry().view<ON::EntityInfo>();
		for (auto e : view) {
			if (ImGui::Button(s.GetRegistry().get<ON::EntityInfo>(e).name.c_str(), ImVec2(100, 20))) {
				sentity = e;
			}
		}
		ImGui::End();

		ImGui::Begin("Properties");
		if (s.GetRegistry().has<ON::EntityInfo>(sentity)){
			ImGui::Text(s.GetRegistry().get<ON::EntityInfo>(sentity).name.c_str());
			if (s.GetRegistry().has<ON::Transform>(sentity)) {
				// Entity
				ImGui::DragFloat2("Position", glm::value_ptr(s.GetRegistry().get<ON::Transform>(sentity).GetPosition()), 0.01f);
				ImGui::DragFloat2("Scale", glm::value_ptr(s.GetRegistry().get<ON::Transform>(sentity).GetScale()));

				//Rotation Code Sorry this is kindof messy
				float rot = (s.GetRegistry().get<ON::Transform>(sentity).GetRotation());
				ImGui::DragFloat("Rotation", &rot);
				s.GetRegistry().get<ON::Transform>(sentity).SetRotation(rot);
			}
			else if(s.GetRegistry().has<ON::Camera>(sentity)){
				// Camera
				ImGui::DragFloat2("Position", glm::value_ptr(s.GetRegistry().get<ON::Camera>(sentity).GetPosition()), 0.01f);

				//Rotation Code Sorry this is kindof messy
				float rot = (s.GetRegistry().get<ON::Camera>(sentity).GetRotation());
				ImGui::DragFloat("Rotation", &rot);
				s.GetRegistry().get<ON::Camera>(sentity).SetRotation(rot);
			}
			else {
				// Invalid
				ON_CORE_ERROR("Invalid Entity!");
			}
		}
		ImGui::End();

		Dockspace::End();
	}
};

ON::Application* ON::CreateApplication() {
	return new EditorApp();
}

void ON::OnLayersCreate() {
	ON::LayerStack::PushLayer(new EditorLayer());
}