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
    x += cos(degressToRadiants(rotation - 90)) * delta * 2;
    y += sin(degressToRadiants(rotation - 90)) * delta * 2;
};

void Player::moveRight(float delta){
    x += cos(degressToRadiants(rotation + 90)) * delta * 2;
    y += sin(degressToRadiants(rotation + 90)) * delta * 2;
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
    {1,1,1},
    {1,0,0},
    {0,1,0},
    {0,0,1},
    {0.7,0.3,0.3},
};

sf::RenderWindow window(sf::VideoMode(1920, 1080), "3d!");
Player player(1.0,1.0,0,90);

float angles[1920];
int fps = 0.5;

sf::Texture testTexture;


int wallmap[20][20] = {
    {1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {3,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,1,1},
    {1,1,3,0,0,7,1,0,1,0,1,0,0,0,1,0,1,0,1,1},
    {1,0,0,0,0,0,2,1,1,0,1,1,1,1,1,0,1,0,1,1},
    {1,1,2,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,1,1},
    {1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,1,1,1,1,1},
    {1,1,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,7,7,7,7,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,7,0,0,7,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,7,0,0,7,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,7,7,7,7,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};
int floormap[20][20] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,3,3,3,1,5,5,5,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,3,3,3,1,5,5,5,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,3,3,3,1,5,5,5,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

sf::Color getColor(int distance, int colorid)
{
    double c = (255.0/1080 * distance);
    return sf::Color(colors[colorid][0] * c,colors[colorid][1] * c,colors[colorid][2] * c);
    //return sf::Color(255,0,0);

}


void calcAngles(int fov, int rect)
{
    float points[rect];
    // -1 / 1 2/90.0
    float step = (tan(degressToRadiants(fov/2.0))*2)/(rect);
    //float planeDist = 1 / (tan(fov/2));
    //cout<<step*rect;
    for(int i = 0; i < rect;i++)
    {
        points[i] = (i * step) -1;
        angles[i] = (atan(points[i]));
    }
}

bool d = true;
void printVector(sf::Vector2f v){
    cout<<v.x <<" "<<v.y<<"\n";
}
void castRay(float angle, int step, float beta) {
    float initx = player.x;
    float inity = player.y;

    float x = initx;
    float y = inity;

    float dx = cos(angle);
    float dy = sin(angle);
    int caststep = 0;
    while(wallmap[(int)(y)][(int)(x)] ==0)
    {
        x+=dx * 0.01;
        y+=dy * 0.01;

        if(caststep > 10000)
        {
            break;
        }
        caststep++;
    };
    int colorid = wallmap[(int)(y)][(int)(x)];
    float fx = x - initx;
    float fy = y - inity;

    float distance = sqrt(fx*fx + fy*fy);

    distance = distance * cos(beta);

    int height = ((1080)/(distance));
    height=max(min(height,1080*32),1);

    //height *= height/abs(height);   
    
    int offset = (1080/2) - (height / 2);



    //floor
    if(height<1080)
    {
        sf::Vector2f v(fx,inity);


        float lengthOfOpp = sqrt((v.x-x)*(v.x-x) + (v.y-y) * (v.y-y));

        float floorstep = lengthOfOpp / offset;

        for(int i = 0; i < offset; i++)
        {
            sf::Vector2f meow(fx,fy-i*floorstep);
            sf::Vector2f s(meow.x*cos(angle) - meow.y*sin(angle), meow.y*sin(angle) + meow.x*cos(angle));

            sf::RectangleShape r(sf::Vector2f(1,1));
            r.setPosition(sf::Vector2f(step,offset+height+i));
            r.setFillColor(sf::Color::Cyan);
            window.draw(r);
            if(d){
                cout<<meow.x<<"\n";//floormap[(int)s.y][(int)s.x]
            }

        }

    }
    if(colorid == 7){

        float axis = (floor((x-(int)(x)) * 100) >1)  ? x : y;

        int column = floor((axis-(int)(axis)) * 100);
    
        sf::Sprite sprite(testTexture);
        sprite.setTextureRect(sf::IntRect(sf::Vector2(column,0), sf::Vector2(1,100)));
    
        sprite.setPosition(sf::Vector2f(step,offset));
        sprite.setScale(1,height/100.0);//
        
        double c = (255.0/1080 * distance);
        sprite.setColor(getColor(min(height,1080),0));
        
        window.draw(sprite);
    }
    else
    {
        sf::RectangleShape r(sf::Vector2f(1,height));
        r.setPosition(sf::Vector2f(step,offset));
        r.setFillColor(getColor(min(height,1080),colorid));
        window.draw(r);
    }
    
};



int movementCheck(int x, int y)
{
    return(wallmap[(int)y][(int)x] == 0);
    
};
int main() {
    
    calcAngles(player.fov,1920);
    //sf::RenderWindow window(sf::VideoMode(1920, 1080), "3d!");
    window.setMouseCursorVisible(false);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(fps);
    player.rotation = 90;
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

            if(movementCheck(player.x+ cos(degressToRadiants(player.rotation - 90)) * delta * 2, player.y + sin(degressToRadiants(player.rotation - 90)) * delta * 2))
            {
                player.moveLeft(delta);
            }
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            if(movementCheck(player.x+ cos(degressToRadiants(player.rotation + 90)) * delta * 2, player.y + sin(degressToRadiants(player.rotation + 90)) * delta * 2))
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
        //sf::RectangleShape r1(sf::Vector2f(1920,1080));
        //r1.setFillColor(sf::Color::White);
        //window.draw(r1);

        //sf::RectangleShape r2(sf::Vector2f(1920,1080/2));
        //r2.setFillColor(sf::Color::Black);
        //window.draw(r2);
  
        for(int i = 0; i <= 1920; i++)
        {
            
            castRay(angles[i]+degressToRadiants(player.rotation),i, angles[i]);
            
        }
        d=false;
        sf::Text text;
        text.setFont(font);
        text.setString(to_string(mouse_movement.x));
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        

        window.draw(text);
        window.display();
    }
    
    return 0;
};


