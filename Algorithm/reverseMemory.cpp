// memory block swap
// by Tian Cao

#include <iostream>
using namespace std;

#define MAXBUFFERSIZE 100

// reverse the memory block 
// goal: |12345| -> |54321|
//
void * reverseMemory(void *pMemory, const size_t memSize)
{
    if(NULL == pMemory) return pMemory;
    if(memSize < 2) return pMemory;
    
    // with two pointers
    char *begin = reinterpret_cast<char *>(pMemory);
    char *end = begin + memSize - 1;
    for(; begin < end; ++begin, --end)
    {
        char memTmp = *begin;
        *begin = *end;
        *end = memTmp;
    }
    // with one pointer
    // char *pBegin = static_cast<char *>(pMemory);
    // for(size_t i = 0; i < memSize/2; i++)
    // {
    //      char memTmp = *(pBegin + i);
    //      *(pBegin + i) = *(pBegin + memSize - 1 - i);
    //      *(pBegin + memSize -1) = memTmp;
    // }
    return pMemory;
}

// swap two adjacent memory block
// // goal: |*****|#####| -> |#####|*****|
void * swapAdjacentMemory(void *pMemory, const size_t headSize, const size_t totalSize)
{
    if(NULL == pMemory) return pMemory;
    if(totalSize < 2) return pMemory;
    if(headSize > totalSize) return pMemory;

    char *pStart = reinterpret_cast<char *>(pMemory);
    reverseMemory(pStart, headSize);
    reverseMemory(pStart+headSize, totalSize - headSize);
    reverseMemory(pStart, totalSize);
    return pMemory;
}

// swap two nonadjacent memory block 
// goal: |*****|$$$$|#####| -> |#####|$$$$|*****|
void * swapNonAdjacentMemory(void *pMemory, const size_t headSize, const size_t tailSize, const size_t totalSize)
{
    if(NULL == pMemory) return pMemory;
    if(totalSize < 2) return pMemory;
    if(headSize >= totalSize || tailSize >= totalSize) return pMemory;
    if(totalSize < (headSize + tailSize)) return pMemory;

    char *pStart = reinterpret_cast<char *>(pMemory);
    reverseMemory(pStart, headSize);
    reverseMemory(pStart+headSize, totalSize-headSize-tailSize);
    reverseMemory(pStart+totalSize-tailSize, tailSize);
    reverseMemory(pStart, totalSize);
    return pMemory;
}

// test case
int main()
{
    //put all test cases in a string array
    //test by a for loop
    //
    
    static const char *stringArr[] = 
    {
        "",
        "ab",
        "abc",
        "abc1234"
    };

    void * resultArr = malloc(MAXBUFFERSIZE); // alloc space to store the result
    if(NULL == resultArr) return 0;

    size_t arrLen = sizeof(stringArr)/sizeof(*stringArr);

    //test swapAdjacentMemory 
    for(size_t i = 0; i < arrLen; ++i)
    {
        memset(resultArr, 0, MAXBUFFERSIZE);
        memcpy(resultArr, stringArr[i], strlen(stringArr[i]));
        swapAdjacentMemory(resultArr, 2, strlen(stringArr[i]));
        printf("%s\n", (char*)resultArr);
    }

    //test swapNonAdjacentMemory
    for(size_t i = 0; i < arrLen; ++i)
    {
        memset(resultArr, 0, MAXBUFFERSIZE);
        memcpy(resultArr, stringArr[i], strlen(stringArr[i]));
        swapNonAdjacentMemory(resultArr, 2,2, strlen(stringArr[i]));
        printf("%s\n", (char*)resultArr);
    }
    free(resultArr);
    return 1;
}
