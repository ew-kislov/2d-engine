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
#include "OpenGL.cpp"

BaseObject::BaseObject(string fragmentShaderSource, string vertexShaderSource, glm::vec2 position, int layer) {
    this->initialPosition = position;
    this->position = position;
    this->layer = layer;

    this->programId = OpenGL::createProgram(vertexShaderSource, fragmentShaderSource);
    OpenGL::useProgram(this->programId);
}

int BaseObject::getLayer() const {
    return this->layer;
}

shared_ptr<Scene> BaseObject::getScene() {
    return Game::getScene(this->scene);
}

glm::vec2 BaseObject::getPosition() {
    return this->position;
}

void BaseObject::setObjectId(string objectId) {
    this->objectId = objectId;
    
    if (this->getScene()) {
        this->getScene()->addNamedObject(this);
    }
}

string BaseObject::getObjectId() {
    return this->objectId;
}

BaseObject::~BaseObject() {
}