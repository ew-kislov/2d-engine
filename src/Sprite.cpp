#pragma once

#include "Sprite.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include "OpenglUtils.cpp"
#include "MathUtils.cpp"

#include "BaseObject.cpp"
#include "Camera.cpp"
#include "Texture.cpp"

#include "OpenGL.cpp"

Sprite::Sprite(Texture* texture, glm::vec2 position, int layer):
    BaseObject("src/fragment_shader.glsl", "src/vertex_shader.glsl", position, layer) {
    this->texture = texture;
    this->height = texture->getHeight();
    this->width = texture->getWidth();
}

void Sprite::init() {
    this->position = this->initialPosition;

    GLfloat z = 1.0 * this->layer / MAX_LAYERS;

    this->vao = OpenGL::createRectVao(0, 0, this->width, this->height, z);
}

void Sprite::draw() {
    if (this->isOutOfWindow()) {
        return;
    }

    OpenGL::useProgram(this->programId);

    glm::mat4 cameraMatrix = Camera::getResultMatrix();
    OpenglUtils::setUniformMat4(
        this->programId,
        "transform_matrix",
        cameraMatrix * glm::translate(glm::vec3(this->position, 0.0f))
    );

    OpenGL::bindTexture(this->texture->getId());
    OpenGL::bindVao(this->vao);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

MathUtils::Rect* Sprite::getBoundingRect() {
    glm::vec4 d0 = glm::vec4(1.0f * this->position.x, 1.0f * this->position.y, 0.0f, 1.0f);
    glm::vec4 d1 = glm::vec4(1.0f * (width + this->position.x), 1.0f * (height + this->position.y), 0.0f, 1.0f);

    return new MathUtils::Rect(d0.x, d0.y, d1.x, d1.y);
}

bool Sprite::isOutOfWindow() {
    MathUtils::Rect* rect = this->getBoundingRect();
    glm::vec2 cameraPosition = Camera::getPosition();

    return rect->y1 + cameraPosition.y < 0 || rect->x1 + cameraPosition.x < 0 || rect->y0 + cameraPosition.y > Window::getHeight() || rect->x0 + cameraPosition.x > Window::getWidth();
}