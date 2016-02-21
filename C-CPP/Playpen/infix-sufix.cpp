#include <iostream>
#include <string>
#include <stack>
using namespace std;

int mycmp(char a, char b) {
    if(b == '(')
        return 1;//左括号直接入栈
    else if((b == '*' || b == '/') &&(a == '+' || a == '-' || a == '('))
        return 1;//*、/优先级高于+、-、(，入栈
    else if((b == '+' || b == '-') && (a == '('))
        return 1;//+、-优先级高于(，入栈
    else
        return 0;
}

/*中缀表达式转后缀表达式
 中缀表达式之间无分割
 后缀表达式操作数、操作符之间用空格分割，便于区分不同操作数*/
void infix_to_suffix(const string infix, string &suffix) {
    int i, k;
    stack<char> stk;//存储运算符的栈

    for(i=0; i < infix.size(); i++) {
        if(infix[i] >= '0' && infix[i] <= '9') {
            suffix += infix[i];//操作数则直接输出
        } else {
            if(i != 0 && infix[i-1] >= '0' && infix[i-1] <= '9') {
                suffix += ' ';//操作数后补充空格分割
            }
            if(infix[i] == ')') {
                //遇到右括号则一直弹出直到左括号，但左括号不输出
                while(stk.top() != '(') {
                    suffix += stk.top();
                    stk.pop();
                    suffix += ' ';
                }
                stk.pop(); // pop "("
            } else if(stk.empty() || mycmp(stk.top(), infix[i])) {
                //栈为空或当前操作符的优先级高于栈顶操作符，当前操作符入栈
                stk.push(infix[i]);
            } else {
                //当前操作符优先级等于或低于栈顶操作符则弹出栈顶
                while(!mycmp(stk.top(), infix[i])) {
                    suffix += stk.top();
                    stk.pop();
                    suffix += ' ';
                    if(stk.empty())
                        break;
                }
                stk.push(infix[i]);//当前操作符入栈
            }
        }
    }
    //补充空格分割
    if(suffix[suffix.size()-1] != ' ') {
        suffix += ' ';
    }
    //如果操作符栈不为空，弹出所有操作符
    while(!stk.empty()) {
        suffix += stk.top();
        stk.pop();
        suffix += ' ';
    }
    //suffix[j] = '\0';
    cout << suffix << endl;
}

/*后缀表达式求值*/
int suffix_value(string suffix) {
    int i, j;
    char op;
    stack<int> stk;
    int top = 0, value = 0;
    for(i=0; suffix[i] != '\0'; i++) {
        if(suffix[i] >= '0' && suffix[i] <= '9') {
            value = value*10 + suffix[i] - '0';
        } else if(suffix[i] == ' ') {
            //操作数入栈
            stk.push(value);
            value = 0;
        } else {
            //根据操作符，对栈顶两个操作数进行计算并得到结果
            int op2 = stk.top(); stk.pop();
            int op1 = stk.top(); stk.pop();
            switch(suffix[i]) {
                case '+': value = op1 + op2;break;
                case '-': value = op1 - op2;break;
                case '*': value = op1 * op2;break;
                case '/': value = op1 / op2;break;
                default: break;
            }
            top -= 2;
        }
    }

    return stk.top();
}


int main() {
    string infix("(23+34*45/(5+6+7))");
    string sufix("");
    infix_to_suffix(infix, sufix);

    cout << suffix_value(sufix) << endl;

}