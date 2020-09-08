#ifndef ANDORA_TIMER_H
#define ANDORA_TIMER_H

#ifdef WIN32
// importing windows.h in global scope results in naming conflicts
namespace hide_win {
#include <windows.h>
}
using Clock = hide_win::LARGE_INTEGER;
#else
#include <time.h>
using Clock = timespec;
#endif

namespace andora {
class Timer {
 public:
  Timer();
  float GetElapsed();

 private:
  Clock start_;
#ifdef WIN32
  hide_win::LARGE_INTEGER cpu_freq_;
#endif

  void Timer::GetClockTime(Clock *t);
};
}  // namespace andora

#endif  // !ANDORA_TIMER_H