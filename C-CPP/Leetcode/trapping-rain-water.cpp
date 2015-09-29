class Solution {
public:
    int trap(vector<int>& height) {
        //method 1: Two Pointers: Time ~ O(N), Space ~ O(1)
        int n = height.size();
        int left = 0, right = n - 1;
        int leftmax = 0, rightmax = 0, sum = 0;
        while(left < right) {
            leftmax = max(leftmax, height[left]);
            rightmax = max(rightmax, height[right]);
            
            if (leftmax < rightmax) {
                sum += leftmax - height[left];
                left++;
            } else {
                sum += rightmax - height[right];
                right--;
            }
        }
        return sum;

        // find left and right max
        /*/ method 2: find left and right max
        vector<int> max_left = vector<int>(n, 0);
        vector<int> max_right = vector<int>(n, 0);
        
        for (int i = 1; i < n; i++) {
            max_left[i] = max(height[i - 1], max_left[i - 1]);
            max_right[n - i - 1] = max(height[n - i], max_right[n - i]);
        }
        
        
        for (int i = 0; i < n; i++) {
            int maxheight = min(max_left[i], max_right[i]);
            sum += maxheight > height[i] ? maxheight - height[i] : 0;
        }
        return sum;
        */
    }
};