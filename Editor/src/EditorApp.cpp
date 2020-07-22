#include <Ongine.h>
#include "EditorLayer.h"

class EditorApp : public ON::Application {
public:

	virtual void OnRun() override {
	}
	virtual void OnUpdate(ON::Input& input) override {
		
	}
	virtual void OnRender() override {
	}
};

ON::Application* ON::CreateApplication() {
	return new EditorApp();
}

void ON::OnLayersCreate() {
	ON::LayerStack::PushLayer(new EditorLayer());
}