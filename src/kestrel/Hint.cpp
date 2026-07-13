struct HINT_s {
    char pad[0x2a];
    unsigned char complete;
    char pad2[13];
    unsigned char flags;
};

unsigned char Hint_isComplete(HINT_s* hint) {
    return hint->complete;
}

int Hint_isActive(HINT_s* hint) {
    return (hint->flags >> 4) & 1;
}

int Hint_AddHint(HINT_s* hint) {
    return 0;
}

void Hint_ResetHint(HINT_s* hint) {
    if (hint != nullptr) {
        hint->complete = 0;
    }
}
