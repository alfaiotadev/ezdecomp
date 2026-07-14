#pragma once

struct NuVideoSettings {
    char pad[0x1510];
    int width;
    int height;
};

extern NuVideoSettings* nuvideo_settings __attribute__((visibility("hidden")));
