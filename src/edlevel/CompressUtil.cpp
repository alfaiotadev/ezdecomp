#include "edlevel/CompressUtil.h"

namespace CompressUtil {
int CompressFloat1(float value) {
    if (value < -1.0f)
        value = -1.0f;
    if (value > 1.0f)
        value = 1.0f;
    return static_cast<int>((value + 1.0f) * 32767.5f);
}
int CompressFloat2(float value) {
    if (value < -1.0f)
        value = -1.0f;
    if (value > 1.0f)
        value = 1.0f;
    return static_cast<int>((value + 1.0f) * 127.5f);
}
int CompressUFloat1(float value) {
    if (value < 0.0f)
        value = 0.0f;
    if (value > 1.0f)
        value = 1.0f;
    return static_cast<int>(value * 65535.0f);
}
int CompressUFloat2(float value) {
    if (value < 0.0f)
        value = 0.0f;
    if (value > 1.0f)
        value = 1.0f;
    return static_cast<int>(value * 255.0f);
}

float UncompressFloat1(unsigned short value) {
    return static_cast<float>(value) / 32767.5f - 1.0f;
}
float UncompressFloat2(unsigned char value) {
    return static_cast<float>(value) / 127.5f - 1.0f;
}
float UncompressUFloat1(unsigned short value) {
    return static_cast<float>(value) / 65535.0f;
}
float UncompressUFloat2(unsigned char value) {
    return static_cast<float>(value) / 255.0f;
}
}  // namespace CompressUtil
