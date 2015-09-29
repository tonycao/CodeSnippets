class Solution {
public:
    string countAndSay(int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if (n <= 0) return string();
        string say = "1";
        for (int i = 1; i < n; i++){
            say = strConvert(say);
        }
        return say;
    }

    string strConvert(const string &say){
        stringstream ss;
        int count = 0;
        char last = say[0];

        for (size_t i = 0; i <= say.size(); i++){
            if(say[i] == last){
                ++count;
            }else{
                ss<<count<<last;
                count = 1;
                last = say[i];
            }
        }
        return ss.str();
    }
};
