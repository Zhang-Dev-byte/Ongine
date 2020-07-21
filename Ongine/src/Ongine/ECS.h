#pragma once
#include "Base.h"
#include <entt.hpp>
#include "Transform.h"
#include "Camera.h"
namespace ON {
	struct ON_API EntityInfo {
		std::string name;
	};
	class ON_API Entity {
	public:
		Entity() = default;
		Entity(EntityInfo info, entt::registry& r);
		template<typename T>
		void AddComponent(T c, entt::registry& r) {
			r.emplace_or_replace<T>(entity, c);
		}
		template<typename T>
		T& GetComponent(entt::registry& r) {
			return r.get<T>(entity);
		}
		template<typename T>
		void RemoveComponent(entt::registry& r) {
			r.remove<T>(entity);
		}
		template<typename T>
		bool HasComponent(entt::registry& r) {
			return r.has<T>(entity);
		}

		inline entt::entity& GetEntity() {
			return entity;
		}
	private:
		entt::entity entity;
		ON::Transform transform;
	};
	class ON_API Scene {
	public:
		entt::registry& GetRegistry();
		void Render();
		void SetCamera(Entity* camera);
	private:
		Entity* c;
		entt::registry r;
	};
}