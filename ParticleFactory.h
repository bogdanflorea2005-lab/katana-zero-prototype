//
// Created by Bogdan on 01-Jan-26.
//

#ifndef OOP_PARTICLEFACTORY_H
#define OOP_PARTICLEFACTORY_H

#include <iostream>
#include <unordered_map>

#include "Particle.h"

class Particle;

//Flyweight factory
class ParticleFactory {
private:
    std::unordered_map<std::string, Particle*> m_particles;
public:
    Particle* getParticle(std::string key) {
        if (m_particles.find(key)==m_particles.end()) {
            m_particles[key]=new Particle(key);
        }
        return m_particles[key];
    }

    friend class Room;
};


#endif //OOP_PARTICLEFACTORY_H