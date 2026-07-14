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

struct NUQFNT {
    int printMode;
};

NUQFNT* g_NuQFnt __attribute__((__visibility__("hidden"))) __attribute__((__aligned__(4096)));

int NuQFntGetPrintMode(void) {
    return g_NuQFnt->printMode;
}
