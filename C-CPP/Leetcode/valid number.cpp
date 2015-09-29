class Solution {
public:
    bool isNumber(const char *s) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        bool bIntNum = false;
        int nCurState = 1;
        while(true){
            if(nCurState == 1){
                while(*s==' ')
                    s++;
                if(*s == '+' || *s == '-')
                    s++;

                if(*s >= '0' && *s <= '9'){
                    while(*s >='0' && *s <='9')
                        s++;
                    bIntNum = true;
                }
                else{
                    if (*s != '.') return false;
                }

                if(*s == '.'){
                    nCurState = 2;
                    s++;
                }else if(*s == 'e'){
                    nCurState = 3;
                    s++;
                }else
                    break;
            }else if(nCurState ==2){
                if(*s>='0' && *s <='9'){
                    while(*s>='0' && *s<='9')
                        s++;
                }else if(!bIntNum ) return false;

                if(*s == 'e'){
                    nCurState = 3;
                    s++;
                }else
                    break;
            }else{
                if(*s=='+'||*s=='-') s++;

                if(*s>='0' && *s<='9'){
                    while(*s>='0' && *s<='9')
                        s++;
                }else
                    return false;

                break;
            }
        }
        while(*s==' ') s++;
        return *s ==0;
    }
};

// 有限状态机
// status 1 => 小数点前面的部分
// status 2 => 小数点后到'e'前面的部分
// status 3 => e后面的科学计数法部分
// 隐含的最后一个status => break 出while loop后的只允许空格的部分
