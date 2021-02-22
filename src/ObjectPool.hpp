#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include <vector>

#include "Camera.hpp"
#include "ControlledObject.hpp"
#include "Tile.hpp"

using namespace std;

class ObjectPool {
    private:
        Camera* camera;
        ControlledObject* controlledObject;
        vector<Tile*> map;

    public:
        ObjectPool();

        void setCamera(Camera* camera) {
            this->camera = camera;
        }

        void setControlledObject(ControlledObject* controlledObject) {
            this->controlledObject = controlledObject;
        }

        void addTile(Tile* tile) {
            this->map.push_back(tile);
        }

        Camera* getCamera() {
            return this->camera;
        }

        ControlledObject* getControlledObject() {
            return this->controlledObject;
        }

        vector<Tile*> getMap() {
            return this->map;
        }
};

#endif