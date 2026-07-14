#include "nu2api/NuSpecial.h"

struct NuSpecialObject {
    char pad[0xa8];
    int instance;
};

int NuSpecialGetInstanceix(nuhspecial_s* special) {
    if (special->object == nullptr) {
        return -1;
    }
    return special->object->instance;
}
