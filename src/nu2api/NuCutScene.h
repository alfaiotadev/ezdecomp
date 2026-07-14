#pragma once

struct NuCutSceneRaw;

void NuSetCutSceneVFXFixUpFn(long (*fn)(const char*, NuCutSceneRaw*, void*));
