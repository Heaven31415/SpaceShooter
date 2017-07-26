#include "Randomizer.hpp"

Randomizer::Randomizer()
: randomDevice()
, engine(randomDevice())
{
}