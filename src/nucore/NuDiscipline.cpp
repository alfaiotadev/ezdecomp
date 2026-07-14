#include "nucore/NuDiscipline.h"

static const char* gNuDisciplineStrs[] = {
    "UNKNOWN",
    "DEFAULT",
};

const char* NuDisciplineGetStr(NuDiscipline discipline) {
    return gNuDisciplineStrs[static_cast<int>(discipline) + 1];
}
