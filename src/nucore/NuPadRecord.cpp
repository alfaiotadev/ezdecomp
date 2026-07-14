#include "nucore/NuPadRecord.h"

struct NuPadRecord {
    char pad[56];
    int playEndButtons;
};

__attribute__((visibility("hidden"))) NuPadRecord* g_pNuPadRecord;

void NuPadRecordSetPlayEndButtons(int buttons) {
    g_pNuPadRecord->playEndButtons = buttons;
}
