#pragma once
#include "Base.h"
#include "Log.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ON {
	class ON_API Camera {
	public:
		Camera(float left, float right, float bottom, float top);

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

		inline void Translate(glm::vec2& value) {
			position += value;
		}
		inline void Rotate(float value) {
			rotation += value;
		}

		inline void RecalculateViewMatrix() {
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));

			view = glm::inverse(transform);

			viewprojection = projection * view;
		}
		
		inline glm::mat4& GetViewMatrix() {
			RecalculateViewMatrix();
			return view;
		}
		inline glm::mat4& GetProjectionMatrix() {
			return projection;
		}
		inline glm::mat4& GetViewProjection() {
			RecalculateViewMatrix();
			return viewprojection;
		}
	private:
		glm::mat4 projection;
		glm::mat4 view;
		glm::mat4 viewprojection;

		glm::vec2 position;
		float rotation = 0.0f;
	};
}