// Copyright (c) 2014   Free Inc.  ALL RIGHTS RESERVED.
// Author: yweiyun@gmail.com (Young Ray)
// Create  2014-10-30

#ifndef BASE_TASK_POOL_H
#define BASE_TASK_POOL_H
#include <vector>
#include <list>
#include "Singleton.h"

namespace base
{
// TaskEntry 需要满足一定的接口条件
template <typename TaskEntry>
class TaskPool : public Singleton<TaskPool<TaskEntry> >
{
public:
    TaskPool();
    ~TaskPool();
    // 初始化接口
    int init(const uint32_t pool_size);
    // 分配task，如果返回NULL，则失败
    TaskEntry* get_task_from_pool(uint32_t *task_id);
    // 通过ID返回task
    TaskEntry* get_task_by_id(const uint32_t task_id);
    // 释放task
    int put_task_to_pool(uint32_t task_id);
    int put_task_to_pool(TaskEntry* task);
private:
    int add_to_free_pool(TaskEntry* task);
    uint32_t pool_size_;
    uint32_t free_size_;
    std::vector<TaskEntry> session_pool_;
    std::list<TaskEntry*> free_pool_;
    TaskEntry* pool_head_;              // 只是为了方便计算索引
    bool free_lock_;                    // gcc build-in 锁
private:
    // DISALLOW_COPY_AND_ASSIGN(TaskPool);
};
} // namespace base
#include "TaskPool.inl"
#endif // BASE_TASK_POOL_H
