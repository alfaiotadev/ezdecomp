#pragma once

class OcclusionManager {
public:
    char pad[0x160];
    float m_occluderDotProductThreshold;
};
