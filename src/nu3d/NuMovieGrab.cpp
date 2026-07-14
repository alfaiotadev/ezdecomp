#include "nu3d/NuMovieGrab.h"

struct NuMovieGrabInfo {
    char pad[0x38];
    int enabled;
};

__attribute__((visibility("hidden"))) NuMovieGrabInfo g_NuMovieGrabInfo;

int NuMovieGrabGetEnabled() {
    return g_NuMovieGrabInfo.enabled;
}
