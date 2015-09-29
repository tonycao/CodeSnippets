class Solution {
public:
    int atoi(const char *str) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (*str == '\0') return 0;

        const char *p = str;
        bool negtive = true;

        // skip spaces
        while(*p == ' ') p++;

        if(*p=='+'){
            negtive = false;
            p++;
        } else if(*p=='-'){
            negtive = true;
            p++;
        }

        // convert
        long ret = 0;
        while(isdigit(*p)){
            int digit = *p-'0';
            ret *= 10;
            ret += digit;

            if(!negtive && ret > INT_MAX) return INT_MAX;
            if(negtive && -ret < INT_MIN) return INT_MIN;
            p++;
        }

        return negtive ? -ret : ret;

    }
};

//algorith 2:
    class Solution {
     public:
         int atoi(const char *str) {
             // Start typing your C/C++ solution below
             // DO NOT write int main() function
             assert(str != NULL);

             while(isspace(*str)) str++;  // remove ' '


             int sign = (*str == '-') ? -1 : 1;

             if (*str == '-' || *str == '+')    // if can check one char
                 str++;

             int ret = 0;
             while(isdigit(*str))   // is digit
             {
                 int digit = *str - '0';

                 if (INT_MAX / 10 >= ret)
                     ret *= 10;
                 else
                     return sign == -1 ? INT_MIN : INT_MAX;

                 if (INT_MAX - digit >= ret)
                     ret += digit;
                 else
                     return sign == -1 ? INT_MIN : INT_MAX;

                 str++;
             }

             return ret * sign;
         }
     };
