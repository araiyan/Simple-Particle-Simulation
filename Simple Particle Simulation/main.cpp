#include "Header Files\ParticleSimulation.h"
#include <cstdlib>
#include <time.h>

#include <SFML/Graphics.hpp>

int main()
{
    srand(time(0));
    float randX, randY;

    TriangleParticlePool particlePool;

    for (int i = 0; i < 100; i++)
    {
        randX = (rand() % 10) - 5;
        randY = (rand() % 10) - 5;
        particlePool.createParticle({200.f + i * 5, 200.f + i * 5 }, {randX, randY});
    }

    for (int i = 0; i < 100; i++)
    {
        randX = (rand() % 10) - 5;
        randY = (rand() % 10) - 5;
        particlePool.createParticle({ 150.f + i * 5, 200.f + i * 5 }, { randX, randY });
    }

    sf::RenderWindow window(sf::VideoMode(600, 800), "Particle Simulator");
    window.setFramerateLimit(144);

    sf::Clock deltaClock;
    sf::Time dT;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        dT = deltaClock.restart();

        window.clear();
        particlePool.update(window, dT);
        window.display();
    }

    return 0;
}