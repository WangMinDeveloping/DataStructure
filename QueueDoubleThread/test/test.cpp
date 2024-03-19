#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>
#include <queue>
#include "../include/queue.h"

#define LOOPTIMES (1024)
long long endTime = 0;
long long beginTime = 0;
pthread_t thread_id[4];

long long mEndTime = 0;
long long mBeginTime = 0;
bool signalOver = false;
bool signalOverSTL = false;

pthread_mutex_t mutex;
queue oQueue;
std::queue<int*> stlQueue;

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

void* ProducerEnqueueMy(void* arg)
{
    beginTime = GetTime();

    for (int i = 0; i < LOOPTIMES; i++)
    {
        if (oQueue.enQueue(new int) != 0)
        {
            break;
        }
    }
    signalOver = true;
    return NULL;
}

void* ConsumerDequeueMy(void* arg)
{
    void* pDequeueMember = NULL;
    while (!signalOver || oQueue.getQueueMemberCount() != 0)
    {
        if (oQueue.deQueue(&pDequeueMember) == 0)
        {
            delete (int*)pDequeueMember;
        }
    }
    endTime = GetTime();
    return NULL;
}

void* ProducerSTLQueue(void* arg)
{   
    mBeginTime = GetTime();
    for (int i = 0; i < LOOPTIMES; i++)
    {
        pthread_mutex_lock(&mutex);
        stlQueue.push(new int);
        pthread_mutex_unlock(&mutex);
    }
    signalOverSTL = true;
    return NULL;
}

void* ConsumerSTLQueue(void* arg)
{
    int beginIndex = 0;
    bool exitFlag = false;
    int *pMem = NULL;
    while (!signalOverSTL || !stlQueue.empty())
    {
        pthread_mutex_lock(&mutex);
        if (!stlQueue.empty())
        {
            pMem = stlQueue.front();
            delete pMem;
            stlQueue.pop();
        }
        pthread_mutex_unlock(&mutex);
    }
    mEndTime = GetTime();
    return NULL;
}

void testMyQueue()
{
    int result = 0;
    int exitFlag = 0;

    if (!oQueue.initialize(LOOPTIMES))
    {
        printf("queue init err\n");
        return;
    }

    result = pthread_create(&thread_id[0], NULL, ProducerEnqueueMy, NULL);
    if (result != 0)
    {
        printf("ProducerEnqueueMy thread create err\n");
    }
    result = pthread_create(&thread_id[1], NULL, ConsumerDequeueMy, NULL);
    if (result != 0)
    {
        printf("ConsumerDequeueMy thread create err\n");
    }

    exitFlag = pthread_join(thread_id[0], NULL);
    if (exitFlag != 0)
    {
        printf("ProducerEnqueueMy thread exit err\n");
    }
    exitFlag = pthread_join(thread_id[1], NULL);
    if (exitFlag != 0)
    {
        printf("ConsumerDequeueMy thread exit err\n");
    }
    printf("My Queue cross time  %lld.\n", endTime - beginTime);
}

void testSTLQueue()
{
    pthread_mutex_init(&mutex,NULL);
    int result = 0;
    int exitFlag = 0;

    result = pthread_create(&thread_id[2], NULL, ProducerSTLQueue, NULL);
    if (result != 0)
    {
        printf("ProducerSTLQueue thread create err\n");
    }
    result = pthread_create(&thread_id[3], NULL, ConsumerSTLQueue, NULL);
    if (result != 0)
    {
        printf("ConsumerSTLQueue thread create err\n");
    }

    exitFlag = pthread_join(thread_id[2], NULL);
    if (exitFlag != 0)
    {
        printf("ProducerSTLQueue thread exit err\n");
    }
    exitFlag = pthread_join(thread_id[3], NULL);
    if (exitFlag != 0)
    {
        printf("ConsumerSTLQueue thread exit err\n");
    }
    printf("STL Queue cross time  %lld.\n", mEndTime - mBeginTime);
}

int main()
{
    testMyQueue();
    testSTLQueue();
    return 0;
}
