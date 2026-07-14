#pragma once

enum NUVIDEO_DISPLAY_TYPE {
    NUVIDEO_DISPLAY_DEFAULT = 0,
};

class NuRenderThreadSetup {
public:
    static int UserDisplay;
};

void NuVideoSetBrightnessPS(void);
int NuVideoGetAspectPS(void);
void NuVideoSetDisplayType(NUVIDEO_DISPLAY_TYPE type);
