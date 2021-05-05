#pragma once

#include <cstdlib>

#include <SFML/Graphics.hpp>

struct TriangleParticle
{
    sf::VertexArray* triangle;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Time lifeTime;

    TriangleParticle* nextParticle;
};

class TriangleParticlePool
{
private:
    TriangleParticle* triangleParticles;

public:
    TriangleParticlePool();
    void createParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Time lifeTime);
    void destroyParticle(int& index);
    void update(sf::RenderWindow& window, sf::Time& dT);
};