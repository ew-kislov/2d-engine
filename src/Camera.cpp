#pragma once

#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include "ObjectPool.cpp"

Camera::Camera() {
    ObjectPool *objectPool = ObjectPool::getInstance();
    if (objectPool->getCamera() != nullptr) {
        throw runtime_error("Camera was already initialized");
    }
    objectPool->setCamera(this);
};

void Camera::setProjection(glm::mat4 projectionMatrix) {
    this->projectionMatrix = projectionMatrix;
}

void Camera::setTargetInitialPosition(ControlledObject* target) {
    this->lookAtMatrix = glm::translate(this->lookAtMatrix, glm::vec3(-target->getInitialPosition().x + 512 - target->getWidth() / 2, -target->getInitialPosition().y + 384 - target->getHeight() / 2, 0.0f));
}

void Camera::moveTarget(glm::vec2 vector) {
    this->lookAtMatrix = glm::translate(this->lookAtMatrix, glm::vec3(-vector.x, -vector.y, 0.0f));
}

glm::mat4 Camera::getProjection() {
    return this->projectionMatrix;
}

glm::mat4 Camera::getTransformation() {
    return this->projectionMatrix * this->lookAtMatrix;
}