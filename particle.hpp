#ifndef PARTICLE_HPP_INCLUDED
#define PARTICLE_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <math.h>

namespace particle
{
struct Particle
{
       short type=0;
       sf::Vector2f position;
       sf::Color color;
};


}
#endif // PARTICLE_HPP_INCLUDED
