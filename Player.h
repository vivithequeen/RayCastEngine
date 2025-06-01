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
    void rotateLeft();
    void rotateRight();
    void moveForwards(float delta);
    void moveBackwards(float delta);
};