#include <iostream> 
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <optional>

using namespace std;
double colors[10][3] = {
    {0,0,0},
    {1,0,0},
    {0,1,0},
    {0,0,1},
    {0.7,0.3,0.3},
};

sf::RenderWindow window(sf::VideoMode(1920, 1080), "3d!");;
int map1[5][5] = {
    {1,2,2,2,3},
    {1,0,0,0,3},
    {1,0,0,0,3},
    {1,0,0,0,3},
    {1,4,4,4,3},

};

sf::Color getColor(int distance, int colorid)
{
    double c = (255.0/1080 * distance);
    return sf::Color(colors[colorid][0] * c,colors[colorid][1] * c,colors[colorid][2] * c);
}

void castRay(float angle, int step, int fov, float initx, float inity, float beta) {
    angle-=M_PI/4;
    float x = initx;
    float y = inity;

    float dx = cos(angle);
    float dy = sin(angle);

    while(map1[(int)(y)][(int)(x)] == 0)
    {
        x+=dx * 0.005;
        y+=dy * 0.005;
    };
    int colorid = map1[(int)(y)][(int)(x)];
    float fx = x - initx;
    float fy = y - inity;

    float distance = sqrt(fx*fx + fy*fy);

    distance = distance * 1080 * 1/5.0 * cos(beta);

    int height = 1080-distance;
    int offset = distance / 2;

    sf::RectangleShape r(sf::Vector2f(1920/fov + 1,height));
    r.setPosition(sf::Vector2f(step * 1920/fov,offset));
    r.setFillColor(getColor(height,colorid));
    window.draw(r);
    
};

double degressToRadiants(float degrees)
{
    return degrees * M_PI / 180.0;
};


int movementCheck(int x, int y)
{
    return(map1[(int)y][(int)x] == 0);
    
};
int main() {
    float rotation = 0;
    int fov = 120;

    float playerx = 2;
    float playery = 2;
    //sf::RenderWindow window(sf::VideoMode(1920, 1080), "3d!");
    

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {

            rotation-=0.05;
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {

            rotation+=0.05;
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            if(movementCheck(playerx+ cos(degressToRadiants(rotation)) * 0.001, playery + sin(degressToRadiants(rotation)) * 0.001))
            {
                playerx += cos(degressToRadiants(rotation)) * 0.001;
                playery += sin(degressToRadiants(rotation)) * 0.001;
            }
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {

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

        for(int i = 0; i < fov; i++)
        {
            castRay(degressToRadiants(i+rotation),i,fov,playerx,playery, degressToRadiants(-45 + i));
        };
        
        window.display();
    }
    
    return 0;
};


