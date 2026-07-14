struct NuDisplayList {
    void* tail;
};

struct NuDisplayListState {
    char pad[16];
    NuDisplayList* currentList;
};

extern "C" __attribute__((visibility("hidden"))) NuDisplayListState g_NuDisplayListState{};

void NuDisplayListEndSubmissionOrderedList() {
    g_NuDisplayListState.currentList->tail = nullptr;
}
