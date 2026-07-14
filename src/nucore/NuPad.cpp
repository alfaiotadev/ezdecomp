struct NUPADRECORD {
    char pad[52];
    int recordEndButtons;
};

__attribute__((visibility("hidden"))) NUPADRECORD padrec;
__attribute__((visibility("hidden"))) NUPADRECORD* g_pPadrec = &padrec;

void NuPadRecordSetRecordEndButtons(int buttons) {
    g_pPadrec->recordEndButtons = buttons;
}
