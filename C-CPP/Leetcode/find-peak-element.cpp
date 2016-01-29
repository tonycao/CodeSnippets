class Solution {
public:
    int findPeakElement(const vector<int> &num) {
        //*/ iterative
        
        int left = 0, right = num.size() - 1;
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if ((mid == 0 || num[mid - 1] < num[mid]) && (mid == num.size() - 1 || num[mid] > num[mid + 1])) 
                return mid;
            else if (mid > 0 && num[mid - 1] > num[mid]){
                right = mid - 1;
            } else if (mid < num.size() - 1 && num[mid + 1] > num[mid]) {
                left = mid + 1;
            } else right--;
        }
        return left; 
        //*/
        
        /* recursive
        if (num.size() <= 1) return 0;
        return findPeakElement(num, 0, num.size()-1);
        //*/
        
    }
    
    int findPeakElement(const vector<int> &num, int i, int j) {
        if (i > j) return -1;
        int mid = i + (j - i) / 2;
        // consider boundary case
        //int left = (mid - 1) < 0 ? INT_MIN : num[mid - 1];
        //int right = (mid + 1) > ( num.size() - 1 ) ? INT_MIN : num[mid + 1];
        if ((mid == 0 || num[mid - 1] < num[mid]) && (mid == num.size() - 1 || num[mid] > num[mid + 1])) {
            return mid;
        } else if (mid > 0 && num[mid - 1] > num[mid]) {
            return findPeakElement(num, i, mid - 1);
        } else if (num[mid + 1] > num[mid]) {
            return findPeakElement(num, mid + 1, j);
        }
    }
};