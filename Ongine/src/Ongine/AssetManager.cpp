#include "AssetManager.h"

void ON::AssetManager::AddSprite(const std::string& name, Sprite& sprite)
{
	sprites.insert(std::make_pair(name, sprite));
}

ON::Sprite& ON::AssetManager::Get(const std::string& name)
{
	return sprites.at(name);
}
