#include "nu2api/FlashElement.h"

char* FlashElement_GetName(FlashElement* element) {
    return element->name;
}

bool FlashElement_HasFont(FlashElement* element) {
    return false;
}

bool FlashElement_IsEnabled(FlashElement* element) {
    return element->enabled;
}

FlashFont* FlashElement_GetFont(FlashElement* /*element*/) {
    return nullptr;
}
