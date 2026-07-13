#include "nucore/NuCheckSum.h"

#include "nucore/thirdparty/md5.h"
#include <cstdio>

NuCheckSum::NuCheckSum(int size, const void* data) {
    md5_state_t state;
    md5_init(&state);
    md5_append(&state, static_cast<const md5_byte_t*>(data), size);
    md5_finish(&state, m_u8);
}
NuCheckSum::NuCheckSum(int count, int* sizes, const void** data) {
    md5_state_t state;
    md5_init(&state);
    for (int i = 0; i < count; i++) {
        md5_append(&state, static_cast<const md5_byte_t*>(data[i]), sizes[i]);
    }
    md5_finish(&state, m_u8);
}
int NuCheckSum::Compare(const NuCheckSum& other) const {
    for (int i = 0; i < 16; i++) {
        if (m_u8[i] < other.m_u8[i]) {
            return -1;
        }
        if (m_u8[i] > other.m_u8[i]) {
            return 1;
        }
    }
    return 0;
}
int NuCheckSum::FromString(const char* str) {
    int sscanfResult = 0;
    char hexPair[3];

    for (int i = 0; i < 16; i++) {
        hexPair[0] = str[i * 2];
        hexPair[1] = str[i * 2 + 1];

        unsigned int parsedValue;
        sscanfResult = sscanf(hexPair, "%x", &parsedValue);

        m_u8[i] = static_cast<std::uint8_t>(parsedValue);
    }

    return sscanfResult;
}
bool NuCheckSum::IsZero() const {
    if (reinterpret_cast<const volatile std::uint32_t*>(this)[0] != 0) {
        return false;
    }
    if (reinterpret_cast<const volatile std::uint32_t*>(this)[1] != 0) {
        return false;
    }
    if (reinterpret_cast<const volatile std::uint32_t*>(this)[2] != 0) {
        return false;
    }

    return reinterpret_cast<const volatile std::uint32_t*>(this)[3] == 0;
}
void NuCheckSum::ToString(char* outBuffer) const {
    char hexChars[] = "0123456789abcdef";

    for (int i = 0; i < 16; ++i) {
        const std::uint8_t currentByte = m_u8[i];

        const std::uint8_t highNibble = currentByte >> 4;
        const std::uint8_t lowNibble = currentByte - (highNibble << 4);

        outBuffer[i * 2] = hexChars[highNibble];
        outBuffer[i * 2 + 1] = hexChars[lowNibble];
    }
    outBuffer[32] = '\0';
}
std::uint32_t NuCheckSum::ToU32() const {
    std::uint32_t temp1 = m_u32[0] ^ m_u32[1];
    std::uint32_t temp2 = m_u32[2] ^ m_u32[3];
    return temp1 ^ temp2;
}
std::uint64_t NuCheckSum::ToU64() const {
    return (static_cast<std::uint64_t>(m_u32[0]) << 32 | m_u32[1])
           ^ (static_cast<std::uint64_t>(m_u32[2]) << 32 | m_u32[3]);
}
