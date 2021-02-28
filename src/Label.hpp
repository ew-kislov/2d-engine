#ifndef LABEL_H
#define LABEL_H

#include <map>
#include <string>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "BaseObject.hpp"
#include "MathUtils.cpp"
#include "Scene.hpp"

using namespace std;

class Label: public BaseObject {
    private:
        string text;
        string fontSource;
        int size;
        glm::vec4 color;

        static constexpr float MIN_Z = 0.4f;

        void setPreview();

    public:
        Label(string text, string fontSource, int size, glm::vec4 color, glm::vec3 position, int layer);

        void transform();
        void draw();
};

#endif