#include "kestrel/cMechTokeniser.h"

bool cMechTokeniser::WhiteSpaceCharacter(const char* c) {
    unsigned int ch = static_cast<unsigned char>(*c) - 9;
    if (ch <= 0x17) {
        return ((0x800013 >> static_cast<unsigned char>(ch)) & 1) != 0;
    }
    return false;
}
