#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <string>
#include <map>

#include "Component.hpp"
#include "Texture.hpp"

using namespace std;

class Animator: public Component {
    private:
        double speed;
        double msPerClip;
        double msSinceLastClip;

        string activeAnimation;
        int activeClip;

        map<string, vector<shared_ptr<Texture> > > animations;

    public:
        Animator(double speed);

        void changeSpeed(double speed);

        void addAnimation(string name, vector<shared_ptr<Texture> > clips);
        void switchAnimation(string name);

        string getActiveAnimation();

        void updateSprite(double deltaTime);
        string getId();
};

#endif