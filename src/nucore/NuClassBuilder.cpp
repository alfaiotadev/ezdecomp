#include "nucore/NuSerialize.h"

class NuQuatBase;
class NuVector3Base;
struct NUVEC;

class NuClassBuilder {
public:
    void HandleType(NuSerialize::FieldType, NuSerialize::FieldType, const void*, const char*, unsigned int);
    void HandleQuat(NuQuatBase* out, const char* name, unsigned int size);
    void HandleVec3(NUVEC* out, const char* name, unsigned int size);
    void HandleVec3(NuVector3Base* out, const char* name, unsigned int size);
};

void NuClassBuilder::HandleQuat(NuQuatBase* out, const char* name, unsigned int size) {
    HandleType(static_cast<NuSerialize::FieldType>(0x11), static_cast<NuSerialize::FieldType>(0x47), out,
               name, size);
}

void NuClassBuilder::HandleVec3(NUVEC* out, const char* name, unsigned int size) {
    HandleType(static_cast<NuSerialize::FieldType>(0x18), static_cast<NuSerialize::FieldType>(0x45), out,
               name, size);
}

void NuClassBuilder::HandleVec3(NuVector3Base* out, const char* name, unsigned int size) {
    HandleType(static_cast<NuSerialize::FieldType>(0xf), static_cast<NuSerialize::FieldType>(0x45), out, name,
               size);
}
