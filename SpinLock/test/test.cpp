#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>
#include <queue>
#include "../include/SpinLock.h"

#define LOOPTIMES (1024*200)

long long GetTime()
{
    long long tmp;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    tmp = tv.tv_sec;
    tmp = tmp * 1000000;
    tmp = tmp + tv.tv_usec;
    return tmp;
}

void testMyLock()
{
    SpinLock myLock;
    long long  beginTime = GetTime();
    for (int i = 0; i < LOOPTIMES; i++)
    {
       myLock.enter();
       myLock.leave();
    }
    long long  endTime = GetTime();
    printf("my lock cross time  %lld.\n", endTime - beginTime);
}

void testPthreadSpinLock()
{
    pthread_spinlock_t spin;
    pthread_spin_init(&spin,0);

    // pthread_mutex_t mutex;
    // pthread_mutex_init(&mutex,NULL);
    long long  beginTime = GetTime();
    for (int i = 0; i < LOOPTIMES; i++)
    {
        pthread_spin_lock(&spin);
        pthread_spin_unlock(&spin);

        // pthread_mutex_lock(&mutex);
        // pthread_mutex_unlock(&mutex);
    }
    long long  endTime = GetTime();
    printf("spin lock cross time  %lld.\n", endTime - beginTime);
}

int main()
{
    testMyLock();
    testPthreadSpinLock();
    return 0;
}
