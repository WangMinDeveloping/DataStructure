#include "../src/doublyList.h"
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>
#include <list>
#define loopTimes (1024)
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

int TestStlList()
{
    std::list<long long> myList;
    long long  beginTime = GetTime();
    for (long long i = 0; i < loopTimes; i++)
    {
        myList.push_back(i);
    }
    std::list<long long>::iterator it = myList.begin();
    std::list<long long>::iterator it_end = myList.end();
    for (;it != it_end; it++);
    long long  endTime = GetTime();
    printf("list cross time  %lld.\n", endTime - beginTime);
    return 0;
}

int TestMyList()
{
    CDoublyList<long long> doublyListInt;
    long long  beginTime = GetTime();
    for (long long  i = 0; i < loopTimes; i++)
    {
        doublyListInt.insertTail(i);
    }
    CDoublyList<long long>::iterator it = doublyListInt.begin();
    CDoublyList<long long>::iterator it_end = doublyListInt.end();
    for (; it != it_end ; ++it);
    long long  endTime = GetTime();
    printf(" CDoublyList cross time  %lld.\n", endTime - beginTime);
    return 0;
}

int main()
{
    TestStlList();
    TestMyList();
    return 0;
}
 
