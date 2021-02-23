#ifndef OPENGL_OBJECT_H
#define OPENGL_OBJECT_H

#include <map>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "MathUtils.cpp"

using namespace std;

enum VboType {
    Position = 1,
    TextureCoords = 2
};

class OpenglObject {
    private:
        const static int MAX_LAYERS = 100;

        char* vertexShaderSource;
        char* fragmentShaderSource;
        char* textureSource;

        GLuint programId;
        GLuint vao;
        GLuint textureId;

        int layer;

        map<VboType, GLuint> vbos;

        void setPreview();

    protected:
        glm::mat4 positionMatrix;
        
        glm::vec3 position;

        int width;
        int height;

        void applyTransformationMatrix(glm::mat4 matrix);

    public:
        OpenglObject(char* vertexShaderSource, char* fragmentShaderSource, char* textureSource, glm::vec3 position, int layer);

        int getLayer() const;
        int getWidth();
        int getHeight();
        glm::vec3 getInitialPosition();

        virtual void transform() = 0;
        virtual MathUtils::Rect* getBoundingRect() = 0;

        void draw();
};

#endif