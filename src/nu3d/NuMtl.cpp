extern "C" float mtl_animation_speed_scale;

void NuDisplayListAnimateMtls(float, float);

void NuMtlAnimate(float f1, float f2) {
    float scale = mtl_animation_speed_scale;
    NuDisplayListAnimateMtls(scale * f1, scale * f2);
}
