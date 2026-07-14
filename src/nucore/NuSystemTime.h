#pragma once

class NuSystemTime {
public:
    unsigned int second;
    unsigned int minute;
    unsigned int hour;
    unsigned int day;
    unsigned int month;
    unsigned int year;

    NuSystemTime(const NuSystemTime&);
    NuSystemTime& operator=(const NuSystemTime&);

    unsigned int AsAndyDaviesTime();
};
