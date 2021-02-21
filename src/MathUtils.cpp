#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include "config.hpp"

namespace MathUtils {
    const glm::mat4 projectionMatrix =
        glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(1, 0, 0)) *
        glm::translate(glm::vec3(-1.0, -1.0, 0.0)) *
        glm::scale(glm::vec3(2.0 / WINDOW_WIDTH, 2.0 / WINDOW_HEIGHT, 0.0));
}