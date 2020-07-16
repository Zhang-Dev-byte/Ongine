#include <Ongine.h>

class Sandbox : public ON::Application {
public:
	virtual void OnRun() override {

	}
	virtual void OnUpdate(ON::Input& input) override {

	}
	virtual void OnRender() override {

	}
};

ON::Application* ON::CreateApplication() {
	return new Sandbox();
}