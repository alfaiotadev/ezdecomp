#include "edtools/file.h"
#include "numath/types.h"

extern float EdFileReadFloat();

void EdFileReadNuVec(NUVEC* v) {
    v->x = EdFileReadFloat();
    v->y = EdFileReadFloat();
    v->z = EdFileReadFloat();
}
