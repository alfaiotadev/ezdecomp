#pragma once

class NuSerialize {
public:
    enum FieldType {
        kQuat = 0x16,
    };

    static int ms_fieldSizes[];
};

int NuSerializeGetFieldSize(NuSerialize::FieldType type);

template <typename T>
NuSerialize::FieldType NuSerializeGetFieldTypeMem();

template <typename T>
const NuSerialize::FieldType NuSerializeGetFieldTypeData();
