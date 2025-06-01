#include <iostream> 
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <optional>
#include "Player.h"

Player::Player(float initx, float inity, float initrotation, int fov)
{
    this-> y = initx;
    this-> x = inity;
    this->rotation = initrotation;
    this->fov = fov;
};

double degressToRadiants(float degrees)
{
    return degrees * M_PI / 180.0;
};

void Player::rotateLeft()
{
    rotation-=0.05;
};

void Player::rotateRight(){
    rotation+=0.05;
}

void Player::moveForwards(float delta){
    x += cos(degressToRadiants(rotation)) * delta * 2;
    y += sin(degressToRadiants(rotation)) * delta * 2;
}
void Player::moveBackwards(float delta){
    x -= cos(degressToRadiants(rotation)) * delta * 4;
    y -= sin(degressToRadiants(rotation)) * delta * 4;
}


using namespace std;
double colors[10][3] = {
    {0,0,0},
    {1,0,0},
    {0,1,0},
    {0,0,1},
    {0.7,0.3,0.3},
};

sf::RenderWindow window(sf::VideoMode(1920, 1080), "3d!");
Player player(1.0,1.0,0,90);


int map1[20][20] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,1,1,0,1,1},
    {1,1,3,0,3,1,1,0,1,0,1,0,1,0,0,0,1,0,1,1},
    {1,1,3,0,3,0,0,0,1,0,1,0,0,0,1,0,1,0,1,1},
    {1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1},
    {1,1,1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,1,1},
    {1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,1,1,1,1,1},
    {1,1,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

};

sf::Color getColor(int distance, int colorid)
{
    double c = (255.0/1080 * distance);
    return sf::Color(colors[colorid][0] * c,colors[colorid][1] * c,colors[colorid][2] * c);
    //return sf::Color(255,0,0);
}

void castRay(float angle, int step, int fov, float beta) {
    angle-=M_PI/4;
    float initx = player.x;
    float inity = player.y;

    float x = initx;
    float y = inity;

    float dx = cos(angle);
    float dy = sin(angle);
    int caststep = 0;
    while(map1[(int)(y)][(int)(x)] == 0)
    {
        x+=dx * 0.005;
        y+=dy * 0.005;
        
        if(caststep > 1000)
        {
            break;
        }
        caststep++;
    };
    int colorid = map1[(int)(y)][(int)(x)];
    float fx = x - initx;
    float fy = y - inity;

    float distance = sqrt(fx*fx + fy*fy);
    float xdistance = distance * cos(beta);
    distance = distance * 1080 * 1/5.0 * cos(beta);

    int height = 1080-distance;
    int offset = distance / 2;

    sf::RectangleShape r(sf::Vector2f(1920/fov + 1,height));
    r.setPosition(sf::Vector2f(step * 1920/fov,offset));
    r.setFillColor(getColor(height,colorid));
    window.draw(r);
    
};


int movementCheck(int x, int y)
{
    return(map1[(int)y][(int)x] == 0);
    
};
int main() {

    //sf::RenderWindow window(sf::VideoMode(1920, 1080), "3d!");
    
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        float delta = deltaTime.asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {

            player.rotateLeft();
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {

            player.rotateRight();
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            if(movementCheck(player.x+ cos(degressToRadiants(player.rotation)) * 0.001, player.y + sin(degressToRadiants(player.rotation)) * 0.001))
            {
                player.moveForwards(delta);
            };
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            if(movementCheck(player.x- cos(degressToRadiants(player.rotation)) * 0.001, player.y - sin(degressToRadiants(player.rotation)) * 0.001))
            {
                player.moveBackwards(delta);
            }
        };

 
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();
        sf::RectangleShape r1(sf::Vector2f(1920,1080));
        r1.setFillColor(sf::Color::White);
        window.draw(r1);

        sf::RectangleShape r2(sf::Vector2f(1920,1080/2));
        r2.setFillColor(sf::Color::Black);
        window.draw(r2);

        for(int i = 0; i < player.fov; i++)
        {
            
            castRay(degressToRadiants(i+player.rotation),i,player.fov, degressToRadiants(-45 + i));
        };
        
        window.display();

    }
    
    return 0;
};


