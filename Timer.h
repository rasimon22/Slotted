//
// Created by rasimon on 9/12/19.
//

#ifndef SLOTTED_TIMER_H
#define SLOTTED_TIMER_H
#include <map>
#include <string>
#include <time.h>


namespace Chron
{
    enum class Scale{Seconds, Milliseconds, Nanoseconds};

    class Timer {
       timespec start, finish;
       std::string run;
       static std::map<std::string, long> times;

    public:
       Timer() = delete;
       Timer(std::string);
       ~Timer();
       static long duration(const std::string&, Scale = Scale::Nanoseconds);

    };
}

#endif //SLOTTED_TIMER_H
