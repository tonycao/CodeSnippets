/*
 约瑟夫环问题(Josephus)
 用户输入M,N值，从1至N开始顺序循环数数，每数到M输出该数值，直至全部输出。写出C程序。（约瑟夫环问题 Josephus）
 Code By Eric Yang 2009
 http://ericyang.cnblogs.com
*/
#include <stdio.h>
#include <stdlib.h>

// 链表节点
typedef struct _RingNode
{
    int pos;  // 位置
    struct _RingNode *next;
}RingNode, *RingNodePtr;

// 创建约瑟夫环，pHead:链表头指针，count:链表元素个数
void CreateRing(RingNodePtr pHead, int count)
{
    RingNodePtr pCurr = NULL, pPrev = NULL;
    int i = 1;
    pPrev = pHead;
    while(--count > 0)
    {
        pCurr = (RingNodePtr)malloc(sizeof(RingNode));
        pCurr->pos = ++i;
        pPrev->next = pCurr;
        pPrev = pCurr;
    }
    pCurr->next = pHead;  // 构成环状链表
}

void PrintRing(RingNodePtr pHead)
{
    RingNodePtr pCurr;
    printf("%d", pHead->pos);
    pCurr = pHead->next;
    while(pCurr != NULL)
    {
        if(pCurr->pos == 1)
            break;
        printf("\n%d", pCurr->pos);
        pCurr = pCurr->next;
    }
}

void KickFromRing(RingNodePtr pHead, int m)
{
    RingNodePtr pCurr, pPrev;
    int i = 1;    // 计数
    pCurr = pPrev = pHead;
    while(pCurr != NULL)
    {
        if (i == m)
        {
            // 踢出环
            printf("\n%d", pCurr->pos);    // 显示出圈循序
            pPrev->next = pCurr->next;
            free(pCurr);
            pCurr = pPrev->next;
            i = 1;
        }
        pPrev = pCurr;
        pCurr = pCurr->next;
        if (pPrev == pCurr)
        {
            // 最后一个
            printf("\n%d", pCurr->pos);    // 显示出圈循序
            free(pCurr);
            break;
        }
        i++;
    }
}

void math(int m, int n){
    int i, s = 0;
    for (i = 2; i <= n; i++)
    {
          s = (s + m) % i;
    }
    printf ("\nThe winner is %d\n", s+1);
}

int main()
{
    int m = 2, n = 20;
    RingNodePtr pHead = NULL;
    printf("---------------Josephus Ring---------------\n");
    printf("N(person count) = %d, ", m);
    //scanf("%d", &n);

    printf("M(out number) = %d\n", n);

    //scanf("%d", &m);
    if(n <= 0 || m <= 0)
    {
        printf("Input Error\n");
        system("pause");
        return 0;
    }
    // 建立链表
    pHead = (RingNodePtr)malloc(sizeof(RingNode));
    pHead->pos = 1;
    pHead->next = NULL;
    CreateRing(pHead, n);

#define _DEBUG
#ifdef _DEBUG
    PrintRing(pHead);
#endif

    // 开始出圈
    printf("\nKick Order: ");
    KickFromRing(pHead, m);    
    printf("\n");

    math(m, n);

    system("pause");
    return 0;
}