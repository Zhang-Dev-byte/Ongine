#pragma once
#include "Base.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ON {
	class ON_API Transform {
	public:
		Transform();

		inline glm::vec2& GetPosition() {
			return position;
		}
		inline void SetPosition(glm::vec2& value) {
			position = value;
		}
		inline float GetRotation() {
			return rotation;
		}
		inline void SetRotation(float value) {
			rotation = value;
		}
		inline glm::vec2& GetScale() {
			return scale;
		}
		inline void SetScale(glm::vec2& value) {
			scale = value;
		}

		inline void Scale(glm::vec2& value) {
			scale += value;
		}
		inline void Translate(glm::vec2& value) {
			position += value;
		}
		inline void Rotate(float value) {
			rotation += value;
		}

		glm::mat4 GetModelMatrix();
		
	private:
		glm::vec2 position;
		glm::vec2 scale;
		float rotation;
	};
}