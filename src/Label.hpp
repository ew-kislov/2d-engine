#ifndef LABEL_H
#define LABEL_H

#include <map>
#include <string>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "UiElement.hpp"
#include "MathUtils.cpp"

using namespace std;

class Label: public UiElement {
    private:
        string text;
        string fontSource;
        int size;
        glm::vec4 color;

    public:
        Label(string text, string fontSource, int size, glm::vec4 color, glm::vec2 position, int layer);

        void init();
        void draw();

        string getClassId();
};

#endif