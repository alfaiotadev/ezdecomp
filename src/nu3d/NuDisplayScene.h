#pragma once

#include "legoapi/BoxGeom.h"

class NuDisplayScene {
public:
    void GetClipObjectLocalExtents(unsigned int, NuVector3Base&, NuVector3Base&) const;
};
