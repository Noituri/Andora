#include "timer.h"

namespace andora {
Timer::Timer() {
  GetClockTime(&start_);
#ifdef WIN32
  hide_win::QueryPerformanceFrequency(&cpu_freq_);
#endif
}

float Timer::GetElapsed() {
  Clock current;
  GetClockTime(&current);
#ifdef WIN32
  return (current.QuadPart - start_.QuadPart) / (float)cpu_freq_.QuadPart;
#else
  return (current.tv_sec - start_.tv_sec) * 1e6 +
         (current.tv_nsec - start_.tv_nsec) / 1e3;
#endif
}

void Timer::GetClockTime(Clock *t) {
#ifdef WIN32
  hide_win::QueryPerformanceCounter(t);
#else
  clock_gettime(CLOCK_MONOTONIC, t);
#endif
}
}  // namespace andora
