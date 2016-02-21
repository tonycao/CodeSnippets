#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool checkForFour(int array[], int length)
{
    for(int i=0; i<length; i++)
    {
        if(array[i] == 4)
            return true;
    }
    return false;
}

void recurse(int array[],int next1, int next2, vector<int> excludedDigits, int length, int pos)
{
    if(pos==length)
    {
        bool is4 = checkForFour(array,length);
        if(is4)
            cout<<"4";
        else
            cout<<array[0];
        for(int i=1; i<length; i++)
            cout<<array[i];
        cout<<endl;
        return;
    }
    for(int i=0; i < 10; i++)
    {
        int prev=array[pos-1];
        cout << pos-1 << " "<< array[pos-1] << endl;
        if((prev==next1 && i==next2) || (prev==next2 && i==next1))
            continue;
        vector<int>::iterator it;
        it = find( excludedDigits.begin(), excludedDigits.end(), i);
        if(it!=excludedDigits.end())
            continue;
        array[pos]=i;
        recurse(array, next1, next2, excludedDigits, length, pos+1);
    }
}

int main(int argc, const char * argv[])
{
    int length;
    cout<<"Enter the length of the phone number\n";
    cin>>length;
    cout<<"Enter the two digits that cannot be next to each other\n";
    int next1,next2;
    cin>>next1>>next2;
    cout<<"Enter the number of digits to be excluded\n";
    int excludedLength;
    cin>>excludedLength;
    vector<int> excludedDigits;
    for(int i=0; i<excludedLength; i++)
    {
        int temp;
        cin>>temp;
        excludedDigits.push_back(temp);
    }
    int* array = new int[length];
    recurse(array, next1, next2, excludedDigits, length, 0);
    return 0;
}