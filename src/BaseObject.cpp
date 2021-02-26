#pragma once

#include "BaseObject.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include "OpenglUtils.cpp"
#include "MathUtils.cpp"

BaseObject::BaseObject(char* fragmentShaderSource, char* vertexShaderSource, glm::vec3 position, int layer) {
    this->vertexShaderSource = vertexShaderSource;
    this->fragmentShaderSource = fragmentShaderSource;
    this->position = position;
    this->positionMatrix = glm::translate(position);
    this->layer = layer;

    this->movementVector = glm::vec2(0.0f, 0.0f);

    this->programId = OpenglUtils::createShaderProgram(this->vertexShaderSource, this->fragmentShaderSource);

    glUseProgram(this->programId);
}

int BaseObject::getLayer() const {
    return this->layer;
}

int BaseObject::getWidth() {
    return this->width;
}

int BaseObject::getHeight() {
    return this->height;
}

glm::vec3 BaseObject::getInitialPosition() {
    return this->position;
}

void BaseObject::applyTransformationMatrix(glm::mat4 matrix) {
    glUseProgram(this->programId);
    OpenglUtils::setUniformMat4(this->programId, "transform_matrix", matrix);
}

Scene* BaseObject::getScene() {
    return this->scene;
}

glm::vec2 BaseObject::getMovement() {
    return this->movementVector;
}