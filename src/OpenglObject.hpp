#ifndef OPENGL_OBJECT_H
#define OPENGL_OBJECT_H

#include <map>

#include <GL/glew.h>

#include <glm/glm.hpp>

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

        int width;
        int height;
        int layer;

        map<VboType, GLuint> vbos;

        void setPreview();

    protected:
        glm::mat4 positionMatrix;

        void applyTransformationMatrix(glm::mat4 matrix);

    public:
        OpenglObject(char* vertexShaderSource, char* fragmentShaderSource, char* textureSource, glm::vec3 position, int layer);

        int getLayer() const;

        virtual void transform(glm::mat4 projectionMatrix) = 0;
        void draw();
};

#endif