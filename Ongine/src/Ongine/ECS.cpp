#include "ECS.h"
#include "Sprite.h"

ON::Entity::Entity(EntityInfo info, entt::registry& r)
{
	entity = r.create();
	r.emplace_or_replace<ON::Transform>(entity, transform);
	r.emplace_or_replace<ON::EntityInfo>(entity, info);
}

entt::registry& ON::Scene::GetRegistry()
{
	return r;
}

void ON::Scene::Render()
{
	auto view = r.view<ON::Sprite, ON::Transform>();
	for (auto entity : view) {
		view.get<ON::Sprite>(entity).Render(c->GetComponent<ON::Camera>(r), view.get<ON::Transform>(entity));
	}
}

void ON::Scene::SetCamera(Entity* camera)
{
	c = camera;
}
