class Solution {
public:
    int candy(vector<int> &ratings) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int len = ratings.size();
        if(len == 0 ) return 0;
        if(len == 1) return 1;
        vector<int> d(len);
        d[0] = 1;

        for(int i=1; i<len; i++){
            if(ratings[i] == ratings[i-1]) d[i] = 1;
            else if(ratings[i] > ratings[i-1]) d[i] = d[i-1] + 1;
            else{
                d[i] = 1;
                if(d[i-1] == 1){
                    int j = i;
                    while(j>0 && ratings[j-1] > ratings[j] && d[j-1] == d[j]){
                        d[j-1]++;
                        j--;
                    }
                }
            }
        }
        int sum = 0;
        for(int i = 0; i<ratings.size(); i++){
            sum += d[i];
        }
        return sum;
    }
};
