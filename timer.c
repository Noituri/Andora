#include "timer.h"

Clock start;

#ifdef WIN32
LARGE_INTEGER cpu_freq;
#endif

void InitTimer()
{
    GetClockTime(&start);
#ifdef WIN32
    QueryPerformanceFrequency(&cpu_freq);
#endif
}

void GetClockTime(Clock *t)
{
#ifdef WIN32
    QueryPerformanceCounter(t);
#else
    clock_gettime(CLOCK_MONOTONIC, t);
#endif
}

float ClockTimeElapsed()
{
    Clock current;
    GetClockTime(&current);
#ifdef WIN32
    return (current.QuadPart - start.QuadPart) / (float) cpu_freq.QuadPart;
#else
    return (current.tv_sec - start.tv_sec) * 1e6 + (current.tv_nsec - start.tv_nsec) / 1e3;
#endif
}