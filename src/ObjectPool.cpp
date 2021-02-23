#pragma once

#include "ObjectPool.hpp"

#include "Camera.cpp"

ObjectPool* ObjectPool::instance {nullptr};
std::mutex ObjectPool::mutex;

ObjectPool::ObjectPool() {
}

ObjectPool::~ObjectPool() {
}

ObjectPool* ObjectPool::getInstance() {
    std::lock_guard<std::mutex> lock(mutex);

    if (instance == nullptr) {
        instance = new ObjectPool();
    }
    return instance;
}

void ObjectPool::setCamera(Camera *camera) {
    this->camera = camera;
}

void ObjectPool::setControlledObject(ControlledObject *controlledObject) {
    this->controlledObject = controlledObject;
}

void ObjectPool::addTile(Tile *tile) {
    this->map.push_back(tile);
}

Camera* ObjectPool::getCamera() {
    return this->camera;
}

ControlledObject* ObjectPool::getControlledObject() {
    return this->controlledObject;
}

vector<Tile*> ObjectPool::getMap() {
    return this->map;
}