#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *pNext;
    Node(int n){
        data = n;
        pNext = NULL;
    }
};

Node *swapListElement(Node *list, int k)
{
    if (list  == NULL)
        return NULL;

    Node *head = list, *prev = list;
    int count = 1;
    Node *tempNode = NULL;
    for(tempNode = head->pNext; tempNode != NULL;)
    {
        if (count == k)
            break;

        prev->pNext = tempNode->pNext;
        tempNode->pNext = head;
        head = tempNode;
        tempNode = prev->pNext;
        count++;
    }
    if(tempNode != NULL)
        prev->pNext = swapListElement(tempNode, k);

    return head;
}

void CleanupList(Node *list)
{
    while(list != NULL){
        Node *tmpNode= list;
        list = list->pNext;
        delete tmpNode;
    }
}

int main(int argc, char const *argv[])
{
    int n, k;
    cout << "Enter no. of elements of linked list:" << endl;
    cin >> n;
    Node *list = NULL, *prevNode = NULL;
    cout << "Enter elements of linked list:" << endl;

    for(int i = 0; i < n; i++){
        int val;
        cin >> val;
        Node *node = new Node(val);
        if(list == NULL){
            list = node;
            prevNode = node;
        }
        else{
            prevNode->pNext = node;
            prevNode = node;
        }
    }
    do {
        cout << "Enter value of k:" << endl;
        cin >> k;
        if(k>n)
            cout << "wrong number"<<endl;
    }while(k>n);

    list = swapListElement(list, k);
    cout<<"linked list after reversing:"<<endl;
    for (Node *tmpNode = list; tmpNode!=NULL; tmpNode=tmpNode->pNext){
        cout<<tmpNode->data<<endl;
    }
    CleanupList(list);
    return 0;
}












