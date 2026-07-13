#pragma once

void EdFileSwapEndianess16(void* data);
void EdFileSwapEndianess32(void* data);
void EdFileSwapEndianess64(void* data);
int EdFileSetReadWrongEndianess(int wrongEndian);
