#include "Transform.h"

ON::Transform::Transform()
{
	rotation = 0;
	position = glm::vec2(0, 0);
	scale = glm::vec2(1.0f, 1.00f);
}

glm::mat4 ON::Transform::GetModelMatrix() {
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(position, 0.0f));
	trans = glm::rotate(trans, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::scale(trans, glm::vec3(scale, 0.0f));
	return trans;
}
