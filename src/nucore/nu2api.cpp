#include "nucore/nu2api.h"

#include <cstdio>

unsigned int NuStrCmp(const char* param_1, const char* param_2);

static eNUAPI_PROJECT g_currentProject = PROJECT_INVALID;

static const char* g_projectNames[PROJECT_COUNT] = {
    "UnknownProject",     // 0
    "Hobbit",             // 1
    "TTAnimation",        // 2
    "LegoHarryPotter",    // 3
    "LegoCloneWars",      // 4
    "LegoCity",           // 5
    "LegoPirates",        // 6
    "LegoHarryPotter2",   // 7
    "WhatsYourNews",      // 8
    "SceneViewer",        // 9
    "LegoSuperHeroes1",   // 10
    "LegoBatmanMovie",    // 11
    "LegoBatman2Shorts",  // 12
    "LegoLOTR",           // 13
    "LegoMarvel",         // 14
    "LegoEmmet",          // 15
    "LegoChima",          // 16
    "UnknownProject",     // 17
    "BuilderGame",        // 18
    "LegoHobbit",         // 19
    "UnknownProject",     // 20
    "LegoOrange",         // 21
    "LegoGreen",          // 22
    "UnknownProject",     // 23
};

unsigned int NU2APIIsLegoProject() {
    unsigned int index = g_currentProject - 4;

    if (index <= PROJECT_LEGO_HOBBIT) {
        unsigned int legoProjectBitmap = 0xEDFCF;
        return legoProjectBitmap >> (index & 0xfffff) & 1;
    }
    return 0;
}
eNUAPI_PROJECT NU2APIGetProject(bool param_1) {
    return g_currentProject;
}
unsigned int NU2APIIsHQRenderProject() {
    unsigned int offset = g_currentProject - PROJECT_LEGO_BATMAN_MOVIE;

    if (__builtin_expect(offset > 5, 0)) {
        return 0;
    }
    constexpr unsigned int bitmap = 0x23;
    return bitmap >> (offset & 0x3f) & 1;
}
void NU2APISetProject(eNUAPI_PROJECT project) {
    g_currentProject = project;
}
char* NU2APIGetProjectName(eNUAPI_PROJECT project) {
    eNUAPI_PROJECT project_idx = project;
    if (project_idx >= 0 && project_idx < PROJECT_COUNT) {
        return const_cast<char*>(g_projectNames[project_idx]);
    }
    return const_cast<char*>("UnknownProject");
}
char* NU2APIGetCurrentProjectName() {
    eNUAPI_PROJECT project_idx = g_currentProject;
    if (project_idx >= 0 && project_idx < PROJECT_COUNT) {
        return const_cast<char*>(g_projectNames[project_idx]);
    }
    return const_cast<char*>("UnknownProject");
}
eNUAPI_PROJECT NU2APIGetProjectFromName(const char* name) {
    for (long i = -1; i < PROJECT_COUNT; i++) {
        const char* projectName
            = static_cast<unsigned int>(i) < PROJECT_COUNT ? g_projectNames[i] : "UnknownProject";
        if (NuStrCmp(name, projectName) == 0) {
            return static_cast<eNUAPI_PROJECT>(i);
        }
    }
    return PROJECT_INVALID;
}

int NU2APIVersionString(char* param_1, int param_2) {
    return std::sprintf(param_1, "NU2API(%s:%d %s %s %s)",
                        "KESTREL-13-03-17-NNX-PS4-XBO-PATCHSUBMISSION_Hotfix", 10387753, "FINAL", "11:48:08",
                        "Nov 22 2021");
}
