/*-
 | This source code is part of PATL (Practical Algorithm Template Library)
 | Released under the BSD License (http://www.opensource.org/licenses/bsd-license.php)
 | Copyright (c) 2005, 2007..2009, Roman S. Klyujkov (uxnuxn AT gmail.com)
-*/
#ifndef PATL_AUX_PERF_TIMER_HPP
#define PATL_AUX_PERF_TIMER_HPP

#include <stdint.h>
//#include <windows.h>

namespace uxn
{
namespace patl
{
namespace aux
{

class performance_timer
{
public:
    performance_timer()
        : start_(0)
        , finish_(0)
    {
        query_frequency();
        start();
    }

    void start()
    {
//        LARGE_INTEGER large;
//        QueryPerformanceCounter(&large);
//        start_ = large.QuadPart;
    }

    void finish()
    {
//        LARGE_INTEGER large;
//        QueryPerformanceCounter(&large);
//        finish_ = large.QuadPart;
    }

    double get_seconds() const
    {
        return
            static_cast<double>(finish_ - start_) /
            static_cast<double>(frequency_);
    }

private:
    static void query_frequency()
    {
        if (frequency_ == 0)
        {
//            LARGE_INTEGER large;
//            QueryPerformanceFrequency(&large);
//            frequency_ = large.QuadPart;
        }
    }

    static int64_t frequency_;
    int64_t start_;
    int64_t finish_;
};

int64_t performance_timer::frequency_ = 0;

} // namespace aux
} // namespace patl
} // namespace uxn

#endif
