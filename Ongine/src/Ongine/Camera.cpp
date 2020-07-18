#include "Camera.h"

ON::Camera::Camera(float left, float right, float bottom, float top) : projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), view(1.0f)
{
}
