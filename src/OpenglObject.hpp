#ifndef OPENGL_OBJECT_H
#define OPENGL_OBJECT_H

#include <map>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "MathUtils.cpp"
#include "Scene.hpp"

using namespace std;

class Scene;

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

        Scene* scene;

        map<VboType, GLuint> vbos;

        void setPreview();

        friend class Scene; 

    protected:
        glm::mat4 positionMatrix;
        
        glm::vec3 position;

        glm::vec2 movementVector;

        int width;
        int height;

        Scene* getScene();

        void applyTransformationMatrix(glm::mat4 matrix);

    public:
        OpenglObject(char* textureSource, glm::vec3 position, int layer);

        int getLayer() const;
        int getWidth();
        int getHeight();
        glm::vec3 getInitialPosition();

        virtual void transform() = 0;
        virtual MathUtils::Rect* getBoundingRect() = 0;

        void draw();
        virtual void move() = 0;

        glm::vec2 getMovement();

        virtual string getClassId() = 0;
};

#endif