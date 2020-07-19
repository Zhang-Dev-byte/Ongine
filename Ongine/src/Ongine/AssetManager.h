#pragma once
#include <string>
#include <map>
#include "Sprite.h"

namespace ON {
	class AssetManager {
	public:
		void AddSprite(const std::string& name, Sprite& sprite);
		Sprite& Get(const std::string& name);
	private:
		std::map<std::string, Sprite> sprites;
	};
}