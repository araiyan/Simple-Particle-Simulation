#include "ParticleSimulation.h"

TriangleParticlePool::TriangleParticlePool()
{
    triangleParticles = nullptr;
}

void TriangleParticlePool::createParticle(sf::Vector2f position, sf::Vector2f velocity,
    sf::Time lifeTime)
{
    TriangleParticle* newTriangle = new TriangleParticle;
    int randomColor;
    
    newTriangle->lifeTime = lifeTime;
    newTriangle->position = position;
    newTriangle->velocity = velocity;
    newTriangle->triangle = new sf::VertexArray(sf::Triangles, 3);

    randomColor = rand() % 255;
    (*newTriangle->triangle)[0].color = sf::Color(randomColor, 0, 0);
    randomColor = rand() % 255;
    (*newTriangle->triangle)[1].color = sf::Color(0, randomColor, 0);
    randomColor = rand() % 255;
    (*newTriangle->triangle)[2].color = sf::Color(0, 0, randomColor);

    newTriangle->nextParticle = triangleParticles;
    triangleParticles = newTriangle;
}

void TriangleParticlePool::destroyParticle(int& index)
{
    TriangleParticle* preTrianglePtr = nullptr;
    TriangleParticle* trianglePtr = triangleParticles;

    for (int i = 0; i < index; i++)
    {
        preTrianglePtr = trianglePtr;
        trianglePtr = trianglePtr->nextParticle;
    }

    if (index == 0)
        triangleParticles = triangleParticles->nextParticle;
    else
        preTrianglePtr->nextParticle = trianglePtr->nextParticle;

    index--;
    delete trianglePtr;
}

void TriangleParticlePool::update(sf::RenderWindow& window, sf::Time& dT)
{
    TriangleParticle* trianglePtr = triangleParticles;
    int index = 0;

    while (trianglePtr)
    {
        trianglePtr->lifeTime -= dT;
        trianglePtr->position += trianglePtr->velocity * dT.asSeconds();
        (*trianglePtr->triangle)[0].position = trianglePtr->position - sf::Vector2f(2.f, 0.f);
        (*trianglePtr->triangle)[1].position = trianglePtr->position - sf::Vector2f(-2.f, 0.f);
        (*trianglePtr->triangle)[2].position = trianglePtr->position - sf::Vector2f(0.f, 2.f);
        window.draw(*trianglePtr->triangle);

        if (trianglePtr->lifeTime.asSeconds() < 0)
        {
            trianglePtr = trianglePtr->nextParticle;
            destroyParticle(index);
        }
        else
            trianglePtr = trianglePtr->nextParticle;

        index++;
    }
}