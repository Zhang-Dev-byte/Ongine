#pragma once
#include <vector>
#include "Layer.h"
namespace ON {
	class LayerStack {
	public:
		static inline void PushLayer(Layer* layer) {
			layers.push_back(layer);
		}
		static inline std::vector<Layer*>::const_iterator begin() {
			return layers.begin();
		}
		static inline std::vector<Layer*>::const_iterator end() {
			return layers.end();
		}
	private:
		static std::vector<Layer*> layers;
	};
}