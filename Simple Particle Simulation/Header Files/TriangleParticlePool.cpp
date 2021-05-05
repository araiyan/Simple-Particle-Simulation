#include "ParticleSimulation.h"

TriangleParticlePool::TriangleParticlePool()
{
    triangleParticles = nullptr;
}

void TriangleParticlePool::createParticle(sf::Vector2f position, sf::Vector2f velocity)
{
    TriangleParticle* newTriangle = new TriangleParticle;
    
    newTriangle->lifeTime = sf::seconds(2.f);
    newTriangle->position = position;
    newTriangle->velocity = velocity;
    newTriangle->triangle = new sf::VertexArray(sf::Triangles, 3);

    (*newTriangle->triangle)[0].color = sf::Color::Blue;
    (*newTriangle->triangle)[1].color = sf::Color::Blue;
    (*newTriangle->triangle)[2].color = sf::Color::Blue;
    
    newTriangle->nextParticle = this->triangleParticles;
    triangleParticles = newTriangle;
}

void TriangleParticlePool::update(sf::RenderWindow& window, sf::Time dT)
{
    TriangleParticle* trianglePtr = triangleParticles;

    while (trianglePtr)
    {
        trianglePtr->lifeTime -= dT;
        trianglePtr->position += trianglePtr->velocity * dT.asSeconds();
        (*trianglePtr->triangle)[0].position = trianglePtr->position - sf::Vector2f(2.f, 0.f);
        (*trianglePtr->triangle)[1].position = trianglePtr->position - sf::Vector2f(-2.f, 0.f);
        (*trianglePtr->triangle)[2].position = trianglePtr->position - sf::Vector2f(0.f, 2.f);
        window.draw(*trianglePtr->triangle);

        trianglePtr = trianglePtr->nextParticle;
    }
}