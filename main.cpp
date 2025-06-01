#include <iostream> 
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <optional>

using namespace std;


int map1[5][5] = {
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,1,1,1,1},

};
float castRay(float angle) {
    float initx = 3;
    float inity = 3;

    float x = initx;
    float y = inity;

    float dx = cos(angle);
    float dy = sin(angle);

    while(map1[(int)(y)][(int)(x)] == 0)
    {
        x+=dx * 0.05;
        y+=dy * 0.05;
    };

    float fx = x - initx;
    float fy = y - inity;

    float distance = sqrt(fx*fx + fy*fy);
    
    return distance;
};
double degressToRadiants(double degrees)
{
    return degrees * M_PI / 180.0;
};

int* raycast(int fov, double playerAngle)
{
    int* lineLengths = new int[fov];
    int index = 0;
    for(int i = (180 - fov) / 2; i < fov + ((180 - fov) / 2); i++)
    {
        lineLengths[index] = (int)(castRay((i+playerAngle) * M_PI/180.0) * 1080 * 1/5.0 );
        index++;
    };
    return lineLengths;
};


sf::Color getColor(int distance)
{
    return sf::Color(0, 0,255.0/1080 * distance);
}
int main() {
    int fov = 90;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "3d!");
    
    cout << castRay(M_PI );
    while (window.isOpen())
    {
        int* rays = raycast(fov, 45);
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
        r1.setFillColor(sf::Color::Green);
        window.draw(r1);

        sf::RectangleShape r2(sf::Vector2f(1920,1080));
        r2.setFillColor(sf::Color::Red);
        window.draw(r2);
        for(int i = 0; i < fov; i++)
        {
            int height = 1080-rays[i];
            int offset = rays[i] / 2;
            sf::RectangleShape r(sf::Vector2f(1920/fov + 1,height));
            r.setPosition(sf::Vector2f(i * 1920/fov,offset));
            r.setFillColor(getColor(height));

            window.draw(r);
        };
        
        window.display();
    }
    
    return 0;
};


