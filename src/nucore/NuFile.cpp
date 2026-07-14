#include "nucore/NuFile.h"

int NuFileExtPlatformBit(int platform) {
    return 1 << platform;
}

__attribute__((noinline)) bool NuSystemTime::operator>(const NuSystemTime& other) {
    if (year > other.year)
        return true;
    if (year < other.year)
        return false;
    if (month > other.month)
        return true;
    if (month < other.month)
        return false;
    if (day > other.day)
        return true;
    if (day < other.day)
        return false;
    if (hour > other.hour)
        return true;
    if (hour < other.hour)
        return false;
    if (minute > other.minute)
        return true;
    if (minute < other.minute)
        return false;
    return second > other.second;
}

int NuFileTimeIsNewer(NuSystemTime t1, NuSystemTime t2) {
    return (t1 > t2) & 1;
}
