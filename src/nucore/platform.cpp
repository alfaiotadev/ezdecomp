signed char this_platform;
int this_platformClass;

bool IsNintendoPlatform() {
    return true;
}

int NuGetCurrPlatform() {
    return this_platform;
}
