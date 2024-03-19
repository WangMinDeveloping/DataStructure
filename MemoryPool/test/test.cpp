#include "../include/MemoryPool.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>

#define LOOPTIMES (1024)
int* arrInt[LOOPTIMES];
long long endTime = 0;
long long beginTime = 0;
pthread_t thread_id[4];

long long mEndTime = 0;
long long mBeginTime = 0;

CMemoryPool memoryPool(LOOPTIMES, 800);

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
    for (int i = 0; i < LOOPTIMES; i++)
    {
        arrInt[i] = nullptr;
    }
      
    beginTime = GetTime();

    for (int i = 0; i < LOOPTIMES; i++)
    {
        arrInt[i] = new int[200];
    }
    return NULL;
}

void* ConsumerDelete(void* arg)
{
    int beginIndex = 0;
    bool exitFlag = false;
    while (!exitFlag)
    {
        for (int i = beginIndex; i < LOOPTIMES; i++)
        {
            if (arrInt[i] != NULL)
            {
                delete[] arrInt[i];
                arrInt[i] = NULL;
            }
            else
            {
                beginIndex = i;
                break;
            }
            
            if (i = (LOOPTIMES - 1) )
            {
                exitFlag = true;
            }
        }
    }
    endTime = GetTime();
    return NULL;
}

void* ProducerMemoryPool(void* arg)
{   
    for (int i = 0; i < LOOPTIMES; i++)
    {
        arrInt[i] = nullptr;
    }
    
    mBeginTime = GetTime();
    for (int i = 0; i < LOOPTIMES; i++)
    {
        arrInt[i] = (int*)memoryPool.pop();
    }
    return NULL;
}

void* ConsumerMemoryPool(void* arg)
{
    int beginIndex = 0;
    bool exitFlag = false;
    while (!exitFlag)
    {
        for (int i = beginIndex; i < LOOPTIMES; i++)
        {
            if (arrInt[i] != NULL)
            {
                memoryPool.push((void *)arrInt[i]);
                arrInt[i] = NULL;
            }
            else
            {
                beginIndex = i;
                break;
            }
            if (i == (LOOPTIMES - 1))
            {
                exitFlag = true;
            }
        }
    }
    mEndTime = GetTime();
    return NULL;
}

void testNewDelete()
{
    int result = 0;
    int exitFlag = 0;
    result = pthread_create(&thread_id[0], NULL, ProducerEnqueueMy, NULL);
    if (result != 0)
    {
        printf("producerNew thread create err\n");
    }
    result = pthread_create(&thread_id[1], NULL, ConsumerDelete, NULL);
    if (result != 0)
    {
        printf("ConsumerDelete thread create err\n");
    }

    exitFlag = pthread_join(thread_id[0], NULL);
    if (exitFlag != 0)
    {
        printf("producerNew thread exit err\n");
    }
    exitFlag = pthread_join(thread_id[1], NULL);
    if (exitFlag != 0)
    {
        printf("ConsumerDelete thread exit err\n");
    }
    printf("new delete cross time  %lld.\n", endTime - beginTime);
}

void testMemory()
{
    int result = 0;
    int exitFlag = 0;

    result = pthread_create(&thread_id[2], NULL, ProducerMemoryPool, NULL);
    if (result != 0)
    {
        printf("ProducerMemoryPool thread create err\n");
    }
    result = pthread_create(&thread_id[3], NULL, ConsumerMemoryPool, NULL);
    if (result != 0)
    {
        printf("ConsumerMemoryPool thread create err\n");
    }

    exitFlag = pthread_join(thread_id[2], NULL);
    if (exitFlag != 0)
    {
        printf("ProducerMemoryPool thread exit err\n");
    }
    exitFlag = pthread_join(thread_id[3], NULL);
    if (exitFlag != 0)
    {
        printf("ConsumerMemoryPool thread exit err\n");
    }
    printf("memory cross time  %lld.\n", mEndTime - mBeginTime);
}

int main()
{
    testNewDelete();
    //testMemory();
    return 0;
}
