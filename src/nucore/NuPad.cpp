struct NuPadRecordData {
    char pad[60];
    int recording;
};

__attribute__((visibility("hidden"))) NuPadRecordData* g_pNuPadRecordData;

void NuPadRecordStart() {
    g_pNuPadRecordData->recording = 1;
}
