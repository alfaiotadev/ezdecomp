#include "endian_utils.h"
#include <algorithm>

void EdFileSwapEndianess16(void* data) {
    auto* ptr = static_cast<unsigned char*>(data);
    std::swap(ptr[0], ptr[1]);
}
void EdFileSwapEndianess32(void* data) {
    auto* ptr = static_cast<unsigned char*>(data);
    std::swap(ptr[0], ptr[3]);
    std::swap(ptr[1], ptr[2]);
}
void EdFileSwapEndianess64(void* data) {
    auto* ptr = static_cast<unsigned char*>(data);
    std::swap(ptr[0], ptr[7]);
    std::swap(ptr[1], ptr[6]);
    std::swap(ptr[2], ptr[5]);
    std::swap(ptr[3], ptr[4]);
}
int EdFileSetReadWrongEndianess(int wrongEndian) {
    return wrongEndian;
}
