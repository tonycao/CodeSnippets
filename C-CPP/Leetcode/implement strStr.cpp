class Solution {
public:
    char *strStr(char *haystack, char *needle) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (haystack == NULL || needle == NULL)
            return NULL;
        int hLen = strlen(haystack);
        int nLen = strlen(needle);

        if (hLen < nLen) return NULL;
        for( int i = 0; i < hLen - nLen + 1; i++){
            int j = 0;
            char* p = &haystack[i];
            for( ; j < nLen; j++){
                if (*p != needle[j])
                    break;
                p++;
            }
            if(j == nLen) return &haystack[i];
        }
        return NULL;
    }
};

//Algorithm 2 : KMP
