class Solution {
public:
    int maxArea(vector<int> &height) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
                int left = 0;
        int right = height.size() - 1;
        int best = 0;
        while( left < right ){
            int temp = min(height[left], height[right]) * (right - left);
            if ( temp > best )
                best = temp;
            if (height[left] <= height[right])
                left++;
            else
                right--;
         }
         return best;
    }
};
