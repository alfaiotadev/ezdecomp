#include "nucore/NuSerialize.h"

class NuQuatBase;
class NuVector3Base;
class NuVector4Base;

int NuSerialize::ms_fieldSizes[] = {
    0, 1, 1, 1, 2, 2, 4, 4, 8, 8, 4, 1, 2, 4, 4, 16, 16, 16, 64, 4,
    16, 16, 16, 64, 12, 16, 16, 64, 64, 4, 4, 4, 0, 0, 0, 0, 0, 16, 8, 16,
    16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 4, 4, 8, 8,
    4, 1, 2, 4, 4, 12, 16, 16, 64, 48, 0, 0, 0, 16,
};

static int* s_pNuSerializeFieldSizes = NuSerialize::ms_fieldSizes;

int NuSerializeGetFieldSize(NuSerialize::FieldType type) {
    return s_pNuSerializeFieldSizes[type];
}

template <>
NuSerialize::FieldType NuSerializeGetFieldTypeMem<bool>() {
    return static_cast<NuSerialize::FieldType>(0x1);
}

template <>
NuSerialize::FieldType NuSerializeGetFieldTypeMem<float>() {
    return static_cast<NuSerialize::FieldType>(0xa);
}

template <>
NuSerialize::FieldType NuSerializeGetFieldTypeMem<NuVector3Base>() {
    return static_cast<NuSerialize::FieldType>(0x14);
}

template <>
NuSerialize::FieldType NuSerializeGetFieldTypeMem<NuQuatBase>() {
    return static_cast<NuSerialize::FieldType>(0x16);
}

template <>
NuSerialize::FieldType NuSerializeGetFieldTypeMem<NuVector4Base>() {
    return static_cast<NuSerialize::FieldType>(0x15);
}

template <>
const NuSerialize::FieldType NuSerializeGetFieldTypeData<NuVector3Base>() {
    return static_cast<NuSerialize::FieldType>(0x45);
}

template <>
const NuSerialize::FieldType NuSerializeGetFieldTypeData<NuQuatBase>() {
    return static_cast<NuSerialize::FieldType>(0x47);
}

template <>
const NuSerialize::FieldType NuSerializeGetFieldTypeData<NuVector4Base>() {
    return static_cast<NuSerialize::FieldType>(0x46);
}
