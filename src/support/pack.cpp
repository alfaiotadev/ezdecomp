int PackShortIntoInt(short a, short b) {
    return ((int)(unsigned short)a << 16) | (unsigned short)b;
}
