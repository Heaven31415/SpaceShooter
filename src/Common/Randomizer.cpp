#include "Randomizer.hpp"

std::random_device Random::random;
std::default_random_engine Random::generator(random());