#pragma once

class MechVehicle {
public:
    void ClearVehicleAnimationContext();

private:
    char pad[136];
    void* m_animationContext;
};
