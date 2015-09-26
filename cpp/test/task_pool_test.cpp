#include "TaskPool.h"
#include "TaskEntry.h"
#include <stdio.h>
using namespace base;
int main(int argc, const char *argv[])
{
    TaskPool<TaskEntry> task_pool_main;
    TaskPool<TaskEntry>* task_pool = TaskPool<TaskEntry>::get_instance();
    task_pool->init(100);
    uint32_t task_id = 0;
    for (int i = 0; i < 10; i++)
    {
        TaskEntry* task = task_pool->get_task_from_pool(&task_id);
        printf("%u\n", task_id);
    }
    return 0;
}
