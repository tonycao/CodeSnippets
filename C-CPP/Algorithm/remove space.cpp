void removespace(char *str){
    char *p1 = str, *p2 = str;
    if(str == NULL || !*str){
        return;
    }

    do {
        while(p2 == ' ')
            p2++;
    }while(*p1++ = *p2++);
}

int countNumWords(const char *str){
    bool inWord = false;
    int wordCount = 0;
    while(*str){
        if(!inWord && isalpha(*str)){
            inWord = true;
            wordCount++;
        }
        else if(inWord && *str == ' '){
            inWord = false;
        }
        str++;
    }
    return wordCount;
}

// Type your C++ code and click the "Run Code" button!
// Your code output will be shown on the left.
// Click on the "Show input" button to enter input data to be read (from stdin).

#include <iostream>
#include <string>
using namespace std;

int main() {
    // Start typing your code here...
    int result=0;
    char str[500];
    char *p=str;
    bool isword=false;
    gets(str);

    while(*p)
    {
        if(isword)
        {
            if(!(*p>='a'&&*p<='z' || *p>='A'&&*p<='Z'))
                isword=false;
        }
        else
        {
            if(*p>='a'&&*p<='z' || *p>='A'&&*p<='Z')
            {
                isword=true;
                result++;
            }
        }
        p++;
    }

    cout << result << endl;


    return 0;
}
