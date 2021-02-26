#pragma once

#include "SpriteOrderer.hpp"

// #include "OpenglObject.cpp"

bool SpriteOrderer::operator()(const OpenglObject* lhs, const OpenglObject* rhs) const {
    return lhs->getLayer() < rhs->getLayer();
}