/**
 * Copyright (C) 2012, California Institute of Technology.
 * All Rights Reserved. U.S. Government Sponsorship Acknowledged.
 * Any commercial use must be negotiated with the Office of
 * Technology Transfer at the California Institute of Technology.
 *
 * Author: Peter Vieira <Peter.Vieira@jpl.nasa.gov>
 * Date: June 2015
 */

/**
 * \file gripTime.h
 * \brief Cross-platform clock class that get nanosecond precision on
 * Linux and Mac, and microsecond precision on Windows.
 */

#ifndef TIMER_H_DEF
#define TIMER_H_DEF

/// Include platform-specific headers
#ifdef WIN32             // Windows system specific
    #include <windows.h>
#elif defined(__APPLE__) // Machintosh
    #include <mach/mach.h>
    // #include <mach/mach_time.h>
    #include <mach/clock.h>
#else                    // Linux based system specific
    #include <time.h>
#endif

/**
 * \namespace grip
 * \brief Namespace for stuff that is used for grip
 */
namespace grip {

    /**
     * \brief Cross-platform inline function for getting the current time in seconds with a resolutions
     * of nanoseconds for Linux and Machintosh, and microseconds for Windows.
     * \return double The time in seconds
     */
    inline double getTime() {
#ifdef WIN32
        LARGE_INTEGER time, freq;
        QueryPerformanceCounter(&time);
        QueryPerformanceFrequency(&freq);
        return (1000LL * time.QuadPart) / freq.QuadPart;
#elif defined(__APPLE__)
        struct timespec ts;
        clock_serv_t cclock;
        mach_timespec_t mts;
        host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
        clock_get_time(cclock, &mts);
        mach_port_deallocate(mach_task_self(), cclock);
        ts.tv_sec = mts.tv_sec;
        ts.tv_nsec = mts.tv_nsec;
        return ts.tv_sec + (1e-9)*ts.tv_nsec;
#else
        struct timespec time;
        clock_gettime(CLOCK_MONOTONIC, &time);
        return time.tv_sec + (1e-9)*time.tv_nsec;
#endif
    }

} // end namespace grip

#endif // TIMER_H_DEF
