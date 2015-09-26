// Copyright (c) 2014	Free Inc.  ALL RIGHTS RESERVED.
// Author: yweiyun@gmail.com (Young Ray)
// Create  2014-10-30

#ifndef TASK_NOTIFIER_H
#define TASK_NOTIFIER_H
#include <pthread.h>
#include <stdint.h>
namespace base
{
class TaskNotifier
{
public:
    TaskNotifier();
    ~TaskNotifier();
    int lock_and_wait(uint32_t time_inms);
    void notify();
private:
    pthread_mutex_t   lock_;
    pthread_cond_t    cond_;
};
} // namespace base
#endif // TASK_NOTIFIER_H
