#include <iostream>

using namespace std;

template <class T>
class Stack{
private:
    T *arr;
    int pt, cap;
public:
    Stack(int capacity){ // constructor
        arr = new T[cap = capacity];
        pt = -1;
    }
    ~Stack(){
        delete [] arr;
    }

    T pop(){
        if(pt == -1){
            throw "stack empty";
        }
        T elem = arr[pt--];
        return elem;
    }

    void push(T elem){
        if (pt == capacity() - 1){
            throw "stack full";
        }
        arr[++pt] = elem;
    }
    int capacity(){
        return cap;
    }

    int len(){
        return pt+1;
    }
};

int main(){
    Stack<int> stack(10);
    for(int i = 1; i < 5; i++){
        stack.push(i);
    }
    for(int i = 1; i < 5; i++){
        cout << stack.pop() << endl;
    }
    return 0;
}
