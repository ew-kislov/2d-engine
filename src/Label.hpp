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

struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class Label: public BaseObject {
    private:
        string text;
        string fontSource;
        int size;
        glm::vec4 color;

        GLuint VAO, VBO;
        std::map<GLchar, Character> Characters;

    protected:

    public:
        Label(string text, string fontSource, int size, glm::vec4 color, glm::vec3 position, int layer);

        void transform();
        void setPreview();
        void draw();
};

#endif