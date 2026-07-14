#pragma once

class NuMaterialManager {
public:
    char pad[0x500];
};

NuMaterialManager* NuMaterialManagerGet();
