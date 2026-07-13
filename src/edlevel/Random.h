#pragma once

float NuRandFloatSeeded(unsigned int* seed);

namespace RandomInstance {
void Initialise();
}  // namespace RandomInstance

namespace RandomNumberGenerator {
float GetRandom(unsigned int offset, float index_base, float min, float max);
}  // namespace RandomNumberGenerator
