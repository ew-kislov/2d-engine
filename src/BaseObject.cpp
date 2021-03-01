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

BaseObject::BaseObject(char* fragmentShaderSource, char* vertexShaderSource, glm::vec2 position, int layer) {
    this->initialPosition = position;
    this->position = position;
    this->layer = layer;

    this->programId = OpenglUtils::createShaderProgram(vertexShaderSource, fragmentShaderSource);
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

Scene* BaseObject::getScene() {
    return this->scene;
}

glm::vec2 BaseObject::getPosition() {
    return this->position;
}

void BaseObject::setObjectId(string objectId) {
    this->objectId = objectId;
}

string BaseObject::getObjectId() {
    return this->objectId;
}

BaseObject::~BaseObject() {
}