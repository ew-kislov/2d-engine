#ifndef SPRITE_H
#define SPRITE_H

#include <map>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "BaseObject.hpp"
#include "MathUtils.cpp"
#include "Scene.hpp"
#include "Texture.hpp"

using namespace std;


class Sprite: public BaseObject {
    private:
        Texture* texture;

        static constexpr float MIN_Z = 0.2f;

        bool isOutOfWindow();

    public:
        Sprite(Texture* texture, glm::vec2 position, int layer);

        void init();
        void draw();

        MathUtils::Rect* getBoundingRect();

        // implement this in final objects

        virtual void onStart() = 0;
        virtual void onUpdate() = 0;

        virtual string getClassId() = 0;
};

#endif