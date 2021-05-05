#include "Header Files\ParticleSimulation.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

#include <SFML/Graphics.hpp>

int main()
{
    srand(time(0));
    float randX, randY, randT;

    TriangleParticlePool particlePool;

    for (int i = 0; i < 100; i++)
    {
        for (int z = 0; z < 100; z++)
        {
            randX = (rand() % 20) - 10;
            randY = (rand() % 20) - 10;
            randT = (rand() % 1000) / 50;
            particlePool.createParticle({ 10.f + i * 2 + z * 5, 50.f + i * 5 }, { randX, randY },
                sf::seconds(randT));
        }
    }

    sf::Time dT, createTime = sf::seconds(0.5f);

    sf::RenderWindow window(sf::VideoMode(600, 800), "Particle Simulator");
    window.setFramerateLimit(144);

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        dT = deltaClock.restart();
        std::cout << 1.f / dT.asSeconds() << std::endl;

        if (createTime.asSeconds() < 0)
        {
            randX = (rand() % 60) - 30;
            randY = (rand() % 60) - 30;
            particlePool.createParticle({ 200.f, 200.f}, { randX, randY }, sf::seconds(10.f));
            createTime = sf::seconds(0.01f);
        }

        window.clear();
        particlePool.update(window, dT);
        window.display();
        createTime -= dT;
    }

    return 0;
}