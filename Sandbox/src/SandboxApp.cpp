#include <Ongine.h>
#include "SandboxLayer.h"

class SandboxApp : public ON::Application {
public:
	ON::Camera camera = ON::Camera(-1.6f, 1.6f, -0.9f, 0.9f);
	ON::Sprite sprite = ON::Sprite("res/image.png");
	ON::Scene s;
	ON::Entity e = ON::Entity({"Entity"}, s.GetRegistry());
	ON::Entity c = ON::Entity({"Camera"}, s.GetRegistry());

	virtual void OnRun() override {
		e.AddComponent<ON::Sprite>(sprite, s.GetRegistry());
		c.AddComponent<ON::Camera>(camera, s.GetRegistry());
		c.RemoveComponent<ON::Transform>(s.GetRegistry());

		s.SetCamera(&c);
	}
	virtual void OnUpdate(ON::Input& input) override {
		
	}
	virtual void OnRender() override {
		ImGui::Begin("Hello");
		ImGui::DragFloat2("Position", glm::value_ptr(e.GetComponent<ON::Transform>(s.GetRegistry()).GetPosition()), 0.01f);
		ImGui::End();

		s.Render();
	}
};

ON::Application* ON::CreateApplication() {
	return new SandboxApp();
}

void ON::OnLayersCreate() {
	ON::LayerStack::PushLayer(new SandboxLayer());
}