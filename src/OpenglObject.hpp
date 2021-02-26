#ifndef OPENGL_OBJECT_H
#define OPENGL_OBJECT_H

#include <map>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "BaseObject.hpp"
#include "MathUtils.cpp"
#include "Scene.hpp"

using namespace std;


class OpenglObject: public BaseObject {
    private:
        char* textureSource;

        GLuint textureId;

    protected:
        void setPreview();

    public:
        OpenglObject(char* textureSource, glm::vec3 position, int layer);

        virtual void transform() = 0;
        virtual MathUtils::Rect* getBoundingRect() = 0;

        void draw();
        virtual void move() = 0;

        virtual string getClassId() = 0;
};

#endif