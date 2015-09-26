#include "TaskNotifier.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
using namespace base;
static void *master_func(void *arg)
{
    TaskNotifier* notifier  = (TaskNotifier*)arg;
    usleep(1000000);
    if (notifier->lock_and_wait(100) < 0)
    {
        printf("timeout \n");
    }
    printf("this is mater_task\n");
    return NULL;
}
static void *slaver_func(void *arg)
{
    TaskNotifier* notifier  = (TaskNotifier*)arg;
    printf("this is slaver_task\n");
    notifier->notify();
    return NULL;
}

int main()
{
    TaskNotifier notifier;
    pthread_t tid[2];
    pthread_create(&tid[0], NULL, master_func, &notifier);
    pthread_create(&tid[1], NULL, slaver_func, &notifier);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    return 0;
}
