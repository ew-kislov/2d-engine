#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

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

class BaseObject {
    private:
        char* vertexShaderSource;
        char* fragmentShaderSource;

        Scene* scene;

        friend class Scene; 

    protected:
        glm::mat4 positionMatrix;
        
        glm::vec3 position;

        glm::vec2 movementVector;

        int width;
        int height;

        const static int MAX_LAYERS = 100;
        int layer;

        GLuint programId;
        GLuint vao;
        map<VboType, GLuint> vbos;

        Scene* getScene();

        virtual void setPreview() = 0;

        void applyTransformationMatrix(glm::mat4 matrix);

    public:
        BaseObject(char* fragmentShaderSource, char* vertexShaderSource, glm::vec3 position, int layer);

        int getLayer() const;
        int getWidth();
        int getHeight();
        glm::vec3 getInitialPosition();

        virtual void transform() = 0;

        virtual void draw() = 0;

        glm::vec2 getMovement();
};

#endif