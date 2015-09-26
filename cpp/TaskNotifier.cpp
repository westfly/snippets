// Copyright (c) 2014	Free Inc.  ALL RIGHTS RESERVED.
// Author: yweiyun@gmail.com (Young Ray)
// Create  2014-10-30

#include "TaskNotifier.h"
#include <time.h>
#include <errno.h>

namespace base
{
TaskNotifier::TaskNotifier()
{
    pthread_mutex_init(&lock_, NULL);
    pthread_cond_init(&cond_, NULL);
}
TaskNotifier::~TaskNotifier()
{
    pthread_cond_destroy(&cond_);
    pthread_mutex_destroy(&lock_);
}
int TaskNotifier::lock_and_wait(uint32_t time_inms)
{
    pthread_mutex_lock(&lock_);
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    long nanosec = time_inms*1000000L;
    nanosec += ts.tv_nsec;
    static const int kNanoInSec = 1000000000L;
    ts.tv_nsec = nanosec % kNanoInSec;
    if (nanosec >= kNanoInSec)
    {
        ts.tv_sec += nanosec/kNanoInSec;
    }
    int ret = 0;
    if(ETIMEDOUT == pthread_cond_timedwait(&cond_, &lock_, &ts))
    {
        ret = -1;
    }
    pthread_mutex_unlock(&lock_);
    return ret;
}
void TaskNotifier::notify()
{
    pthread_cond_signal(&cond_);
}
} // namespace base
