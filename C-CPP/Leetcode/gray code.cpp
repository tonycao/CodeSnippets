class Solution {
public:
    unsigned int binary2gray(unsigned int bi){
        return (bi>>1)^bi;
    }
    vector<int> grayCode(int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<int> res;
        for (unsigned int i = 0; i < pow(2,n); ++i)
        {
            res.push_back(binary2gray(i));
        }
        return res;
    }
};
