#pragma once

struct NuSystemTime {
    unsigned int second;
    unsigned int minute;
    unsigned int hour;
    unsigned int day;
    unsigned int month;
    unsigned int year;

    __attribute__((noinline)) bool operator>(const NuSystemTime& other);
};

int NuFileExtPlatformBit(int platform);
int NuFileTimeIsNewer(NuSystemTime t1, NuSystemTime t2);
