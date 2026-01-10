//
// Created by Bogdan on 01-Jan-26.
//

#ifndef OOP_PARTICLEFACTORY_H
#define OOP_PARTICLEFACTORY_H


#include <unordered_map>

#include "Particle.h"

class Particle;

//Flyweight factory
class ParticleFactory {
private:
    std::unordered_map<std::string, Particle*> m_particles;
public:
    Particle* getParticle(const std::string &key) {
        if (!m_particles.contains(key)) {
            m_particles[key]=new Particle(key);
        }
        return m_particles[key];
        //returns a string that represents a file path to a particle texture
    }

    friend class Room;
};


#endif //OOP_PARTICLEFACTORY_H