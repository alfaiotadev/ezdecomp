#include "nu3d/NuRender.h"

struct NuRndrParticleState {
    char pad[32];
    NUMTX* particleRotation;
};

static NuRndrParticleState g_NuRndrParticleState;

void NuRndrSetParticleRotation(NUMTX* rotation) {
    g_NuRndrParticleState.particleRotation = rotation;
}

void NuDrawBounds(const NuVector3Base&, const NuVector3Base&, NUMTX*, NUCOLOUR3 const&) {}
