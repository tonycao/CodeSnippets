// algorithm 1
void swap(int &a, int &b){
    b = a - b;
    a = a - b;
    b = a + b;
}

// algorithm 2
void swap(int &a, int &b){
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

// algorithm 3
void swap(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}
