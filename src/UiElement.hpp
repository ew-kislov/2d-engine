#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include <map>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "BaseObject.hpp"
#include "MathUtils.cpp"

using namespace std;

class UiElement: public BaseObject {
    protected:
        static constexpr float MIN_Z = 0.4f;

        void setPreview() = 0;

    public:
        UiElement(char* fragmentShaderSource, char* vertexShaderSource, glm::vec2 position, int layer);

        void transform();
        void draw() = 0;

        virtual string getClassId() = 0;
};

#endif