#include "nucore/NuThread.h"

#include <nn/os.h>
#include <nn/time.h>

void NuThreadSleep(int ms) {
    nn::os::SleepThread(nn::TimeSpan::FromMilliSeconds(ms));
}
