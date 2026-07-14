extern "C" float nuqfnt_space_width;

void NuQFntSetSpaceWidth(void* /*unused*/, float width) {
    nuqfnt_space_width = width;
}
