#include "nucore/NuString.h"

struct NuOnlineErrorInDLCInfo {
    int error;
    char name[256];
};

static NuOnlineErrorInDLCInfo g_NuOnlineErrorInDLCInfo;

int NuOnlineErrorInDLC() {
    return g_NuOnlineErrorInDLCInfo.error;
}

void NuOnlineSetErrorInDLC(int error, char* name) {
    g_NuOnlineErrorInDLCInfo.error = error;
    if (name != nullptr) {
        NuStrCpy(g_NuOnlineErrorInDLCInfo.name, name);
    }
}

char* NuOnlineGetErrorInDLCName() {
    return g_NuOnlineErrorInDLCInfo.name;
}
