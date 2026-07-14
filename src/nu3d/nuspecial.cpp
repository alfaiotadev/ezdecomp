#include "nu3d/nuspecial.h"

unsigned int NuSpecialWasExported(nuhspecial_s* special) {
    return special->data->flags >> 31;
}
