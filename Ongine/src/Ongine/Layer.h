#pragma once
#include "Base.h"
namespace ON {
	class ON_API Input;
	class ON_API Layer {
	public:
		virtual void OnRun() = 0;
		virtual void OnUpdate(ON::Input& input) = 0;
		virtual void OnRender() = 0;
	};
}