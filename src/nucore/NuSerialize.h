#pragma once

class NuSerialize {
public:
    enum FieldType {
        kQuat = 0x16,
    };
};

template <typename T>
NuSerialize::FieldType NuSerializeGetFieldTypeMem();

template <typename T>
const NuSerialize::FieldType NuSerializeGetFieldTypeData();
