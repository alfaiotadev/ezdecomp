#include "kestrel/TimeOfDay.h"

namespace CityTimeOfDay {
static TimeOfDay timeOfDay = UNKNOWN;

void SetTimeOfDay(TimeOfDay newTime) {
    timeOfDay = newTime;
}
void SetTimeOfDay(const char* timeName) {
    timeOfDay = UNKNOWN;

    if (!timeName) {
        return;
    }

    switch (static_cast<unsigned char>(timeName[0])) {
    case 'N':
    case 'n':
        if (NuStrICmp(timeName, "NOON") == 0) {
            timeOfDay = NOON;
        }
        return;
    case 'D':
    case 'd':
        if (NuStrICmp(timeName, "DAWN") == 0) {
            timeOfDay = DAWN;
            return;
        }
        if (NuStrICmp(timeName, "DUSK") == 0) {
            timeOfDay = DUSK;
        }
        break;
    default:
        break;
    }
}
TimeOfDay GetTimeOfDay() {
    return timeOfDay;
}
const char* GetTimeOfDayName() {
    static const char* timeNames[] = {"NOON", "DAWN", "DUSK"};
    if (static_cast<unsigned>(timeOfDay) <= 2) {
        return timeNames[timeOfDay];
    }
    return "UNKNOWN";
}
}  // namespace CityTimeOfDay
