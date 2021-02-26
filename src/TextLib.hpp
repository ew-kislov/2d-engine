#ifndef TEXT_LIB_H
#define TEXT_LIB_H

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>

using namespace std;

struct Character {
    unsigned int textureId;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};

class TextLib {
    private:
        static map<char, Character*> characters;
        static string fontSource;
        static int size;
        
        static FT_Library lib;

        static void initLib();

    public:
        static void initFont(string pFontSource, int fontSize);
        static Character* getChar(char c);
};

#endif