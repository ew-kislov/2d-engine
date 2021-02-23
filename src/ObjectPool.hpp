#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include <vector>
#include <mutex>

#include "Camera.hpp"
#include "ControlledObject.hpp"
#include "Tile.hpp"

using namespace std;

class ControlledObject;
class Camera;

class ObjectPool {
    private:
        Camera* camera = nullptr;
        ControlledObject* controlledObject = nullptr;
        vector<Tile*> map;

        static ObjectPool* instance;
        static std::mutex mutex;

        ObjectPool();
        ~ObjectPool();

    public:
        ObjectPool(ObjectPool&) = delete;
        void operator=(const ObjectPool&) = delete;

        static ObjectPool* getInstance();

        void setCamera(Camera* camera);
        void setControlledObject(ControlledObject* controlledObject);
        void addTile(Tile* tile);

        Camera* getCamera();
        ControlledObject* getControlledObject();
        vector<Tile*> getMap();
};

#endif