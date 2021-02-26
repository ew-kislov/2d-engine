#ifndef BASE_SPRITE_ORDERER_H
#define BASE_SPRITE_ORDERER_H

#include "OpenglObject.hpp"

class OpenglObject; // TODO: delete

struct BaseSpriteOrderer {
    virtual bool operator()(const OpenglObject* lhs, const OpenglObject* rhs) const = 0;
};

#endif