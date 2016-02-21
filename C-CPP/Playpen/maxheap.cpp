// 最大堆实现, 数组下标从1开始，a[0]不使用。

// 交换两数
void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

// 把第i个元素向上移动
void ShiftUp(int a[], int i) {
    while(i>1 && a[i]>a[i/2]) {
        swap(a[i], a[i/2]);
        i >>= 1;
    }
}

// 把第i个元素向下移动
void ShiftDown(int a[], int n, int i) {
    while((i=2*i) <= n) { //search for i's children
        if(i+1<=n && a[i+1]>a[i]) ++i; // find the largest a[i]
        if(a[i] > a[i/2]) swap(a[i], a[i/2]); // switch largest a[i] with its parent
        else break;
    }
}

// 把数组a变成具备最大堆性质的数组
void MakeHeap(int a[], int n) {
    for(int i=n/2; i>0; --i)
        ShiftDown(a, n, i);
}

// 向堆中插入元素x
void Insert(int a[], int &n, int x) {
    a[++n] = x;
    ShiftUp(a, n);
}

// 删除堆中第i个元素
void Del(int a[], int &n, int i) {
    a[i] = a[n--];
    if(i>1 && a[i]>a[i/2]) ShiftUp(a, i);
    else ShiftDown(a, n, i);
}

// 堆排序，时间复杂度O(nlogn)
void HeapSort(int a[], int n) {
    MakeHeap(a, n);
    for(int i=n; i>1; --i) {
        swap(a[i], a[1]);
        ShiftDown(a, i-1, 1);
    }
}


