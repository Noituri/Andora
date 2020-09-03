#ifndef ANDORA_TIMER_H
#define ANDORA_TIMER_H

#ifdef WIN32
// Not tested
#include <Windows.h>
typedef LARGE_INTEGER Clock;
#else
#include <time.h>
typedef struct timespec Clock;
#endif

void InitTimer();
void GetClockTime(Clock *t);
float ClockTimeElapsed();

#endif //ANDORA_TIMER_H
