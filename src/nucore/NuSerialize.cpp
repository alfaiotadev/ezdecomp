#include "nucore/NuSerialize.h"

class NuQuatBase;
class NuVector3Base;
class NuVector4Base;

void* (*NuSerialize::s_createFieldFuncs[41])(void);

void* NuSerializeCreateField(NuSerialize::FieldType type) {
    return NuSerialize::s_createFieldFuncs[type]();
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
