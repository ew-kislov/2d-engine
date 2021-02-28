#pragma once

#include "SpriteOrderer.hpp"

// #include "OpenglObject.cpp"

bool SpriteOrderer::operator()(const Sprite* lhs, const Sprite* rhs) const {
    return lhs->getLayer() < rhs->getLayer();
}