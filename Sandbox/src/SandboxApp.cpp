#include <Ongine.h>
#include <entt.hpp>

class Sandbox : public ON::Application {
public:
	ON::Camera camera = ON::Camera(-1.6f, 1.6f, -0.9f, 0.9f);
	ON::Sprite sprite = ON::Sprite("res/image.png");
	ON::Transform t = ON::Transform();
	entt::registry r;
	entt::entity e;
	entt::entity c;
	virtual void OnRun() override {
		e = r.create();
		r.emplace_or_replace<ON::Transform>(e, t);
		r.emplace_or_replace<ON::Sprite>(e, sprite);

		c = r.create();
		r.emplace_or_replace<ON::Camera>(c, camera);
		//TODO: Add Scene System and ECS
	}
	virtual void OnUpdate(ON::Input& input) override {

	}
	virtual void OnRender() override {
		ImGui::Begin("Hello");
		ImGui::DragFloat2("Position", glm::value_ptr(t.GetPosition()), 0.01f);
		ImGui::End();
		r.emplace_or_replace<ON::Transform>(e, t);
		r.emplace_or_replace<ON::Sprite>(e, sprite);

		r.emplace_or_replace<ON::Camera>(c, camera);

		auto view = r.view<ON::Sprite, ON::Transform>();
		for (auto entity : view) {
			view.get<ON::Sprite>(entity).Render(r.get<ON::Camera>(c), view.get<ON::Transform>(entity));
		}
	}
};

ON::Application* ON::CreateApplication() {
	return new Sandbox();
}