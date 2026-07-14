#pragma once

struct NuSoundSystem {
    enum MemoryDiscipline {
        Sample = 1,
    };

    static int sAllocdMemory[3];
};

int NuSound_GetAllocdSampleMemory();
