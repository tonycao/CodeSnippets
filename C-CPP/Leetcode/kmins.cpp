//copyright@ 泡泡鱼
//July、2010.06.02。

//@lingyun310：先对元素数组原地建最小堆，O(n)。然后提取K次，但是每次提取时，
//换到顶部的元素只需要下移顶多k次就足够了，下移次数逐次减少。此种方法的复杂度为O（n+k^2）。
#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 123456
#define K 100

//
void HeapAdjust(int array[], int i, int Length)
{
    int child,temp;
    for(temp=array[i];2*i+1<Length;i=child)
    {
        child = 2*i+1;
        if(child<Length-1 && array[child+1]<array[child])
            child++;
        if (temp>array[child])
            array[i]=array[child];
        else
            break;
        array[child]=temp;
    }
}

void Swap(int* a,int* b)
{
    *a=*a^*b;
    *b=*a^*b;
    *a=*a^*b;
}

int GetMin(int array[], int Length,int k)
{
    int min=array[0];
    Swap(&array[0],&array[Length-1]);

    int child,temp;
    int i=0,j=k-1;
    for (temp=array[0]; j>0 && 2*i+1<Length; --j,i=child)
    {
        child = 2*i+1;
        if(child<Length-1 && array[child+1]<array[child])
            child++;
        if (temp>array[child])
            array[i]=array[child];
        else
            break;
        array[child]=temp;
    }

    return min;
}

void Kmin(int array[] , int Length , int k)
{
    for(int i=Length/2-1;i>=0;--i)
        //初始建堆，时间复杂度为O(n)
        HeapAdjust(array,i,Length);

    int j=Length;
    for(int i=k;i>0;--i,--j)
        //k次循环，每次循环的复杂度最多为k次交换，复杂度为o(k^2)
    {
        int min=GetMin(array,j,i);
        printf("%d,", min);
    }
}

int main()
{
    int array[MAXLEN];
    for(int i=MAXLEN;i>0;--i)
        array[MAXLEN-i] = i;

    Kmin(array,MAXLEN,K);
    return 0;
}

// quick select
//copyright@ mark allen weiss
//July、updated，2011.05.05凌晨.

//q_select places the kth smallest element in a[k]
void q_select( input_type a[], int k, int left, int right )
{
    int i, j;
    input_type pivot;
    if( left + CUTOFF <= right )
    {
        pivot = median3( a, left, right );
        //取三数中值作为枢纽元，可以消除最坏情况而保证此算法是O（N）的。不过，这还只局限在理论意义上。
        //稍后，除了下文的第二节的随机选取枢纽元，在第四节末，您将看到另一种选取枢纽元的方法。

        i=left; j=right-1;
        for(;;)
        {
            while( a[++i] < pivot );
            while( a[--j] > pivot );
            if (i < j )
                swap( &a[i], &a[j] );
            else
                break;
        }
        swap( &a[i], &a[right-1] ); /* restore pivot */
        if( k < i)
            q_select( a, k, left, i-1 );
        else
            if( k > i )
                q-select( a, k, i+1, right );
    }
    else
        insert_sort(a, left, right );
}


//maximum heap
//借助堆，查找最小的k个数
//copyright@ yansha &&July
//July、updated，2011.04.28。
#include <iostream>
#include <assert.h>
using namespace std;
void MaxHeap(int heap[], int i, int len);
/*-------------------
BUILD-MIN-HEAP(A)
1  heap-size[A] ← length[A]
2  for i ← |_length[A]/2_| downto 1
3       do MAX-HEAPIFY(A, i)
*/
// 建立大根堆
void BuildHeap(int heap[], int len)
{
    if (heap == NULL)
        return;

    int index = len / 2;
    for (int i = index; i >= 1; i--)
        MaxHeap(heap, i, len);
}
/*----------------------------
PARENT(i)
   return |_i/2_|
LEFT(i)
   return 2i
RIGHT(i)
   return 2i + 1
MIN-HEAPIFY(A, i)
1 l ← LEFT(i)
2 r ← RIGHT(i)
3 if l ≤ heap-size[A] and A[l] < A[i]
4    then smallest ← l
5    else smallest ← i
6 if r ≤ heap-size[A] and A[r] < A[smallest]
7    then smallest ← r
8 if smallest ≠ i
9    then exchange A[i] <-> A[smallest]
10         MIN-HEAPIFY(A, smallest)
*/
//调整大根堆
void MaxHeap(int heap[], int i, int len)
{
    int largeIndex = -1;
    int left = i * 2;
    int right = i * 2 + 1;

    if (left <= len && heap[left] > heap[i])
        largeIndex = left;
    else
        largeIndex = i;

    if (right <= len && heap[right] > heap[largeIndex])
        largeIndex = right;

    if (largeIndex != i)
    {
        swap(heap[i], heap[largeIndex]);
        MaxHeap(heap, largeIndex, len);
    }
}
int main()
{
    // 定义数组存储堆元素
    int k;
    cin >> k;
    int *heap = new int [k+1];   //注，只需申请存储k个数的数组
    FILE *fp = fopen("data.txt", "r");   //从文件导入海量数据（便于测试，只截取了9M的数据大小）
    assert(fp);

    for (int i = 1; i <= k; i++)
        fscanf(fp, "%d ", &heap[i]);

    BuildHeap(heap, k);      //建堆

    int newData;
    while (fscanf(fp, "%d", &newData) != EOF)
    {
        if (newData < heap[1])   //如果遇到比堆顶元素kmax更小的，则更新堆
        {
            heap[1] = newData;
            MaxHeap(heap, 1, k);   //调整堆
        }

    }

    for (int j = 1; j <= k; j++)
        cout << heap[j] << " ";
    cout << endl;

    fclose(fp);
    return 0;
}
