#pragma once

namespace CompressUtil {
int CompressFloat1(float value);
int CompressFloat2(float value);
int CompressUFloat1(float value);
int CompressUFloat2(float value);

float UncompressFloat1(unsigned short value);
float UncompressFloat2(unsigned char value);
float UncompressUFloat1(unsigned short value);
float UncompressUFloat2(unsigned char value);
}  // namespace CompressUtil
