#include "edlevel/Random.h"

namespace RandomInstance {
float m_randomTable[1024];

void Initialise() {
    unsigned int seed = 0xffddffdd;
    for (float& i : m_randomTable) {
        i = NuRandFloatSeeded(&seed);
    }
}
}  // namespace RandomInstance

namespace RandomNumberGenerator {

float GetRandom(unsigned int offset, float index_base, float min, float max) {
    int index = static_cast<int>(index_base) + offset & 0x3FF;

    float randomValue = RandomInstance::m_randomTable[index];
    return (max - min) * randomValue + min;
}

}  // namespace RandomNumberGenerator
