class Solution {
public:
    int lengthOfLastWord(const char *s) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        const char *p = s;
        const char *start = p;
        int len = 0;
        while(*p!='\0'){
            if(*p == ' '){
                len = p - start;
                while(*p == ' ') p++;
                start = p;
                continue;
            }
            p++;
        }
        if(*start != '\0')
            len = p - start;
        return len;
    }
};
