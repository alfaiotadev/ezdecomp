#pragma once

#include <cstdint>

class NuSerialize;
template <bool>
class NuDynamicStringT;

// todo implement Serialize, ToString
class NuCheckSum {
public:
    NuCheckSum(int size, const void* data);
    NuCheckSum(int count, int* sizes, const void** data);
    int Compare(const NuCheckSum& other) const;
    int FromString(const char* str);
    bool IsZero() const;
    void Serialize(NuSerialize& serializer);
    void ToString(char* outBuffer) const;
    void ToString(NuDynamicStringT<false>& outString) const;
    std::uint32_t ToU32() const;
    std::uint64_t ToU64() const;

private:
    union {
        std::uint8_t m_u8[16];
        std::uint32_t m_u32[4];
    };
};
