#pragma once

#ifdef WIN32
// importing windows.h in global scope results in naming conflicts
namespace win {
#include <windows.h>
}
using Clock = win::LARGE_INTEGER;
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
  Clock start_{};
#ifdef WIN32
  win::LARGE_INTEGER cpu_freq_;
#endif

  void GetClockTime(Clock *t);
};
}  // namespace andora