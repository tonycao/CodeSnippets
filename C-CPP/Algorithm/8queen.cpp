#include <iostream>

using namespace std;

int c[10] = {0}, n = 8, cnt = 0;

void print(){
    //cout<<n<<endl;
    for(int i =0; i < n ; i++){
        for(int j = 0; j < n; j++){
            if(j == c[i] ) cout<< "1 ";
            else cout << "0 ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void search(int r){
    if(r == n){
        print();
        cnt++;
        return;
    }
    for(int i = 0 ; i < n; i++){
        //cout << i<<" ";
        c[r] = i;
        int ok = 1;
        for(int j = 0; j < r; j++){
            //cout<< j<< " ";
            if(c[r] == c[j] || r - j == c[r] - c[j] || r - j == c[j] - c[r]){
                ok = 0;
                break;
            }
        }
        if(ok) search(r+1);
        //cout<<endl;
    }
}

int main(){
    search(0);
    cout<< cnt << endl;
    return 0;
}
