#pragma once

#include "Game.hpp"

#include <iostream>
#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include "Sprite.cpp"
#include "SpriteOrderer.cpp"
#include "ControlledObject.cpp"
#include "Tile.cpp"
#include "UiElement.cpp"
#include "Camera.cpp"
#include "Window.cpp"
#include "Scene.cpp"

std::map<string, Scene*> Game::scenes = {};
Scene* Game::activeScene = nullptr;

Game::Game() {
}

void Game::init() {
    Camera::setResolution(Window::getWidth(), Window::getHeight());
}

void Game::runMainLoop() {
    do {
        Window::clear();

        activeScene->runKeyHandlers();

        Camera::move();

        updatePositions();
        draw();

        Window::update();

    } while (Window::isOpened());
}

void Game::draw() {
    auto sprites = activeScene->getSprites();

    for (Sprite* sprite : sprites) {
        sprite->draw();
    }

    set<Label*> ui = activeScene->getUi();

    for (Label* label : ui) {
        label->draw();
    }
}

void Game::updatePositions() {
    auto sprites = activeScene->getSprites();

    for (Sprite* sprite : sprites) {
        sprite->onUpdate();
    }

    set<Label*> ui = activeScene->getUi();

    for (Label* label : ui) {
        label->transform();
    }
}

void Game::addScene(string name, Scene* scene) {
    scenes[name] = scene;
}

void Game::setActiveScene(string name) {
    activeScene = scenes[name];
}