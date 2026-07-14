int NuFntPrintChar(char) {
    return 1;
}

unsigned char NuFntToLower(unsigned char) {
    return 0x20;
}

unsigned char NuFntToUpper(unsigned char) {
    return 0x20;
}

void NuFntSetPen(unsigned int) {}

struct NUFNT;

NUFNT* NuFntCreate(char*, int, int, int, char*) {
    return nullptr;
}

int NuFntGetScreenHeight(NUFNT*) {
    return 1;
}

extern int theSceneObjectHelperPtr;

int NuQFntGetCoordinateSystem() {
    return theSceneObjectHelperPtr;
}
