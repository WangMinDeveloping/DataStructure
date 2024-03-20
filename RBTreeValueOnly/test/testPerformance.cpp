#include "../include/rbTreeValueOnly.h"
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>
#include <map>
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

int TestStlMap()
{
    std::map<int, int> stlMap;
    long long  beginTime = GetTime();
    for (int i = 0; i < loopTimes; i++)
    {
        stlMap.insert(std::make_pair(i,i));
    }
    long long  endTime = GetTime();
    printf("multi map cross time  %lld.\n", endTime - beginTime);
    return 0;
}

int TestMymap()
{
    CRedBlackTree<int, int> myTree;
    long long  beginTime = GetTime();
    for (int  i = 0; i < loopTimes; i++)
    {
        myTree.insert(i, i);
    }
    long long  endTime = GetTime();
    printf(" my RBTree cross time  %lld.\n", endTime - beginTime);
    return 0;
}

int main()
{
    TestStlMap();
    TestMymap();
    return 0;
}
 
