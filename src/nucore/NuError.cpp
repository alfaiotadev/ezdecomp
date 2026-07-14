#include <cstdio>

static const char NuErrorPrintPS_fmt[] = "%s";

int NuErrorPrintPS(const char* msg) {
    return std::printf(NuErrorPrintPS_fmt, msg);
}
