#include <iostream> 
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <optional>
#include <string>
#include "Player.h"
#include <thread>
#include <chrono>
#include <unistd.h> 

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
double radiantsToDegress(float radiants)
{
    return radiants * 180.0 / M_PI;
}

void Player::moveLeft(float delta)
{
    x += cos(degressToRadiants(rotation + 90)) * delta * 2;
    y += sin(degressToRadiants(rotation + 90)) * delta * 2;
};

void Player::moveRight(float delta){
    x += cos(degressToRadiants(rotation - 90)) * delta * 2;
    y += sin(degressToRadiants(rotation - 90)) * delta * 2;
}

void Player::moveForwards(float delta){
    x += cos(degressToRadiants(rotation)) * delta * 2;
    y += sin(degressToRadiants(rotation)) * delta * 2;
}
void Player::moveBackwards(float delta){
    x -= cos(degressToRadiants(rotation)) * delta * 2;
    y -= sin(degressToRadiants(rotation)) * delta * 2;
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
Player player(1.0,1.0,0,60);
float angles[120];
int fps = 0.5;

sf::Texture testTexture;


int map1[20][20] = {
    {1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {3,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,1,1},
    {1,1,3,0,3,7,1,0,1,0,1,0,0,0,1,0,1,0,1,1},
    {1,0,0,0,0,0,2,1,1,0,1,1,1,1,1,0,1,0,1,1},
    {1,1,2,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,1,1},
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


void calcAngles(int fov)
{
    float points[fov];
    // -1 / 1 2/90.0
    float step = 2.0/(fov-1);
    for(int i = 0; i < fov; i++)
    {
        points[i] = (i * step) - 1;
    }

    for(int i = 0; i < fov;i++)
    {

        angles[i] = (atan((1-step*i)));
    }
}

void castRay(float angle, int step, int fov, float beta) {
    //angle-=M_PI/4;
    float initx = player.x;
    float inity = player.y;

    float x = initx;
    float y = inity;

    float dx = cos(angle);
    float dy = sin(angle);
    int caststep = 0;
    while(map1[(int)(y)][(int)(x)] == 0)
    {
        x+=dx * 0.1;
        y+=dy * 0.1;
        
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

    distance = distance  * cos(beta);

    int height = ((1080)/(distance));
    height=max(min(height,1080),1);

    int offset = (1080/2) - (height / 2);

    if(colorid == 7){
        int column = floor((x-(int)(x)) * 10);
        cout << x << "\n";
        sf::Sprite sprite(testTexture);
        sprite.setTextureRect(sf::IntRect(sf::Vector2(column,0), sf::Vector2(1,10)));

        sprite.setPosition(sf::Vector2f(step * 1920/fov,offset));
        sprite.setScale(1920/fov + 1,height/10);//
        window.draw(sprite);
    }
    else
    {
        sf::RectangleShape r(sf::Vector2f(1920/fov + 1,height));
        r.setPosition(sf::Vector2f(step * 1920/fov,offset));
        r.setFillColor(getColor(height,colorid));
        window.draw(r);
    }
    
};


int movementCheck(int x, int y)
{
    return(map1[(int)y][(int)x] == 0);
    
};
int main() {
    
    calcAngles(player.fov);
    //sf::RenderWindow window(sf::VideoMode(1920, 1080), "3d!");
    window.setMouseCursorVisible(false);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(fps);
    sf::Clock clock;
    sf::Font font;
    font.loadFromFile("PixelOperator.ttf");
    sf::Vector2i lastMousePos;
    lastMousePos = sf::Mouse::getPosition();

    testTexture.loadFromFile("test_image.png");

    while (window.isOpen())
    {
        sf::Vector2i mouse_movement =  lastMousePos - sf::Mouse::getPosition();
        lastMousePos = sf::Mouse::getPosition();

        //sf::Mouse::setPosition({1920/2,1080/2},window);
        player.rotation-=mouse_movement.x * 0.5;
        sf::Time deltaTime = clock.restart();
        float delta = deltaTime.asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {

            if(movementCheck(player.x+ cos(degressToRadiants(player.rotation + 90)) * delta * 2, player.y + sin(degressToRadiants(player.rotation + 90)) * delta * 2))
            {
                player.moveLeft(delta);
            }
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            if(movementCheck(player.x+ cos(degressToRadiants(player.rotation - 90)) * delta * 2, player.y + sin(degressToRadiants(player.rotation - 90)) * delta * 2))
            {
                player.moveRight(delta);
            }
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            if(movementCheck(player.x+ cos(degressToRadiants(player.rotation)) * delta * 2, player.y + sin(degressToRadiants(player.rotation)) * delta * 2))
            {
                player.moveForwards(delta);
            };
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            if(movementCheck(player.x- cos(degressToRadiants(player.rotation)) * delta * 2, player.y - sin(degressToRadiants(player.rotation)) * delta * 2))
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
            
            castRay(angles[i]+degressToRadiants(player.rotation),i,player.fov, degressToRadiants(-45 + i));
        };
        sf::Text text;
        text.setFont(font);
        text.setString(to_string(mouse_movement.x));
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        
        sf::Sprite sprite(testTexture);
        sprite.setTextureRect(sf::IntRect(sf::Vector2(0,0), sf::Vector2(1,32)));
        sprite.scale(5,5);
        window.draw(sprite);

        window.draw(text);
        window.display();
    }
    
    return 0;
};


