#include <iostream>
using namespace std;

class Player
{
    public:
    float x;
    float y;
    float rotation;
    int fov;

    Player(float initx, float inity, float initrotation, int fov);
    void moveLeft(float delta);
    void moveRight(float delta);
    void moveForwards(float delta);
    void moveBackwards(float delta);
};