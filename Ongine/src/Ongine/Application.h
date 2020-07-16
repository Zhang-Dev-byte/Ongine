#pragma once
namespace ON {
	class Input;
	class Application {
	public:
		virtual void OnRun() = 0;
		virtual void OnUpdate(ON::Input& input) = 0;
		virtual void OnRender() = 0;
	};
}