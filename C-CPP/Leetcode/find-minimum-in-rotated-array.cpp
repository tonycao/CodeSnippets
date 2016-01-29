class Solution {
public:
    int findMin(vector<int> &num) {
        int left = 0, right = num.size() - 1;
        while(left < right && num[left] >= num[right]) {
            int mid = left + (right - left) / 2;
            if (num[right] < num[mid]) {
                left = mid + 1;
            }else if (num[right] > num[mid]){
                right = mid;
            }else {
                left++;
            }
        }
        return num[left];
    }
};