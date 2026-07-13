#pragma once

struct FlashGraph;

struct FlashScene {
    char pad0[8];
    FlashGraph* graph;
    char pad1[8];
    int animCount;
    char pad2[36];
    void* system;
};

FlashGraph* FlashScene_GetGraph(FlashScene* scene);
void* FlashScene_GetSystem(FlashScene* scene);
int FlashScene_GetAnimCount(FlashScene* scene);
