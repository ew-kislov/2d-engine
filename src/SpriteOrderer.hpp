#ifndef SPRITE_ORDERER_H
#define SPRITE_ORDERER_H

#include "OpenglObject.hpp"

class OpenglObject;

struct SpriteOrderer {
    bool operator()(const OpenglObject* lhs, const OpenglObject* rhs) const;
};

#endif