#pragma once

#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include "ObjectPool.cpp"

Camera::Camera(int width, int height) {
    this->width = width;
    this->height = height;

    this->setProjection();

    ObjectPool *objectPool = ObjectPool::getInstance();
    if (objectPool->getCamera() != nullptr) {
        throw runtime_error("Camera was already initialized");
    }
    objectPool->setCamera(this);
};

void Camera::setProjection() {
    this->projectionMatrix =
        glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(1, 0, 0)) *
        glm::translate(glm::vec3(-1.0, -1.0, 0.0)) *
        glm::scale(glm::vec3(2.0 / this->width, 2.0 / this->height, 1.f));
}

void Camera::setTargetInitialPosition(ControlledObject* target) {
    this->lookAtMatrix = glm::translate(this->lookAtMatrix, glm::vec3(-target->getInitialPosition().x + this->width / 2 - target->getWidth() / 2, -target->getInitialPosition().y + this->height / 2 - target->getHeight() / 2, 0.0f));
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