#include <iostream>
#include <vector>

using namespace std;

vector<string> res;

void print_paren(vector<char> paren_list){
    for(int i = 0; i< paren_list.size(); i++){
        cout<<paren_list[i];
    }
    cout<<endl;
}

void paren(int num_open, int num_close, vector<char> paren_list){
    if(num_open+num_close == 0) {
        print_paren(paren_list);
        //res.push_back(paren_list);
        return;
    }

    if((num_close-num_open) > 0 && num_close > 0){
        paren_list.push_back(')');
        paren(num_open, num_close-1, paren_list);
        paren_list.pop_back();//backtracking
    }
    if(num_open > 0){
        paren_list.push_back('(');
        paren(num_open-1, num_close, paren_list);
        paren_list.pop_back();//backtracking
    }
}

void paren_gen(int n){
    cout << "n = " << n <<endl;
    vector<char> paren_list;
    paren(n, n, paren_list);
    cout << "-----" << endl;
}

int main(){
    paren_gen(2);
    paren_gen(3);
    paren_gen(4);
    return 0;
}
