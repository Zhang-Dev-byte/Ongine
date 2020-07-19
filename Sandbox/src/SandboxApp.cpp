#include <Ongine.h>

class Sandbox : public ON::Application {
public:
	ON::Camera camera = ON::Camera(-1.6f, 1.6f, -0.9f, 0.9f);
	ON::Sprite sprite = ON::Sprite("res/image.png");
	ON::AssetManager manager;
	virtual void OnRun() override {
		manager.AddSprite("A", sprite);
	}
	virtual void OnUpdate(ON::Input& input) override {

	}
	virtual void OnRender() override {
		manager.Get("A").Render(camera);
	}
};

ON::Application* ON::CreateApplication() {
	return new Sandbox();
}