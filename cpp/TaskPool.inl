// Copyright (c) 2014	Free Inc.  ALL RIGHTS RESERVED.
// Author: yweiyun@gmail.com (Young Ray)
// Create  2014-10-30
namespace base
{
template<typename TaskEntry>
TaskPool<TaskEntry>::TaskPool()
{
    free_lock_ = false;
    free_size_ = 0;
}
template<typename TaskEntry>
TaskPool<TaskEntry>::~TaskPool()
{
    for (size_t i = 0; i < pool_size_; ++i)
    {
        TaskEntry* task = &(session_pool_[i]);
        task->destroy();  // 接口依赖
    }
}
template<typename TaskEntry>
int TaskPool<TaskEntry>::init(const uint32_t pool_size)
{
    if (pool_size <= 0)
    {
        pool_size_ = 1024;
    }
    else
    {
        pool_size_ = pool_size;
    }
    // operator ==
    session_pool_.resize(pool_size_);
    for (size_t i = 0; i < pool_size_; ++i)
    {
        TaskEntry* task = &(session_pool_[i]);
        task->init();  // 初始化接口
        task->reset(); // 重用接口
        add_to_free_pool(task);
    }
    pool_head_ = &(session_pool_[0]);
    return 0;
}

template<typename TaskEntry>
TaskEntry* TaskPool<TaskEntry>::get_task_from_pool(uint32_t *task_id)
{
    if (free_size_ < 2)
    {
        return NULL;
    }
    while (!__sync_bool_compare_and_swap(&free_lock_, false, true))
        ;
    // double check
    if (free_size_ < 2)
    {
        free_lock_ = false;
        return NULL;
    }
    TaskEntry* task = free_pool_.front();
    free_pool_.pop_front();
    __sync_sub_and_fetch(&free_size_, 1);
    free_lock_ = false;
    *task_id = task - pool_head_;
    return  task;
}
template<typename TaskEntry>
int TaskPool<TaskEntry>::put_task_to_pool(const uint32_t task_id)
{
    TaskEntry* task = NULL;
    if ((task = get_task_by_id(task_id))!= NULL)
    {
        return -1;
    }
    return put_task_to_pool(task);
}
template<typename TaskEntry>
int TaskPool<TaskEntry>::put_task_to_pool(TaskEntry* task)
{
    task->reset();          // 接口依赖
    add_to_free_pool(task);
    return 0;
}

template<typename TaskEntry>
TaskEntry* TaskPool<TaskEntry>::get_task_by_id(uint32_t task_id)
{
    if (task_id >= pool_size_)
    {
        return NULL;
    }
    return &(session_pool_[task_id]);
}
template<typename TaskEntry>
int TaskPool<TaskEntry>::add_to_free_pool(TaskEntry* task)

{
    while (!__sync_bool_compare_and_swap(&free_lock_, false, true))
        ;
    free_pool_.push_back(task);
    __sync_add_and_fetch(&free_size_, 1);
    free_lock_ = false;
    return 0;
}
/*
template <class T>
TaskPool<T>*
Singleton<TaskPool<T> >::m_inst_ = 0;
template<>
TaskPool<TaskEntry>* Singleton<TaskPool<TaskEntry> >::m_inst_ = 0;
*/
} // namespace base
