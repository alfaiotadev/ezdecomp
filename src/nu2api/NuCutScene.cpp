extern "C" {
int (*NuCutSceneSFXFixUp)(char*) = 0;
}

void NuSetCutSceneSFXFixUpFn(int (*f)(char*)) {
    NuCutSceneSFXFixUp = f;
}
