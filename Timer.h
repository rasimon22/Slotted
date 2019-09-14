//
// Created by rasimon on 9/12/19.
//

#ifndef SLOTTED_TIMER_H
#define SLOTTED_TIMER_H

#include <map>
#include <string>
#include <time.h>


namespace Chron {
    enum class Scale {
        Seconds, Milliseconds, Nanoseconds
    };

    class Timer {
        timespec start, finish;
        std::string run;
        static std::map<std::string, unsigned long long> times;

    public:
        Timer() = delete;

        explicit Timer(std::string);

        explicit Timer(const char *);

        ~Timer();

        static unsigned long long duration(const std::string &, Scale = Scale::Nanoseconds);

        static unsigned long long duration(const char *, Scale = Scale::Nanoseconds);

    };
}

#endif //SLOTTED_TIMER_H
