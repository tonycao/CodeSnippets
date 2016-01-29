class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        /*/ method 1: two pointers
        int localsum = 0, prev = 0, minlen = INT_MAX;
        for (int i = 0; i < nums.size(); i++) {
            localsum += nums[i];
            while (localsum - nums[prev] >= s) localsum -= nums[prev++];
            if (localsum >= s) minlen = min(minlen, i - prev + 1);
            //if (i - j + 1 > minlen) localsum -= nums[j++];
        }
        //if (minlen == INT_MAX) return 0;
        return minlen > nums.size() ? 0 : minlen;
        */
        
        // method 2: integral sum
        int n = nums.size();
        vector<int> sum(n + 1, 0);
        //sum[0] = nums[0];
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + nums[i - 1];
        }
        
        int len = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (sum[i] + s > sum[n]) break;
            int end = binarySearch(i + 1, n, sum[i] + s, sum);
            len = min(len, end - i);
        }
        return len == INT_MAX ? 0 : len;
    }
    
    private:
    int binarySearch(int low, int high, int key, vector<int> &sum){
        while(low < high) {
            int mid = low + (high - low) / 2;
            if (sum[mid] < key) low = mid + 1;
            else if (sum[mid] > key) high = mid;
            else return mid;
        }
        return low;
    }
};