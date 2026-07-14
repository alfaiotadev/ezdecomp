#pragma once

struct NuCutSceneRaw;

extern long (*NuCutScenePTLFixUp)(const char*, NuCutSceneRaw*, void*);

void NuSetCutScenePTLFixUpFn(long (*fn)(const char*, NuCutSceneRaw*, void*));
