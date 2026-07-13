#pragma once

class NuSerialize {
public:
    enum FieldType {
        kQuat = 0x16,
    };

    static void* (*s_createFieldFuncs[])(void);
};

void* NuSerializeCreateField(NuSerialize::FieldType type);

template <typename T>
NuSerialize::FieldType NuSerializeGetFieldTypeMem();

template <typename T>
const NuSerialize::FieldType NuSerializeGetFieldTypeData();
