class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(height.empty()) return 0;
        vector<int> l(height.size(),0);
        vector<int> r(height.size(),0);

        for(int i = 0; i < height.size(); ++i){
            int j = i;
            while((j>0) && (height[i] <= height[j-1])) j = l[j-1];
            l[i] = j;
        }

        for(int i = height.size()-1; i >= 0; --i){
            int j = i;
            while((j < height.size()-1) && (height[i] <= height[j+1])) j = r[j+1];
            r[i] = j;
        }

        int maxa = 0;
        for (int i = 0; i < l.size(); ++i)
        {
            maxa = max(maxa, ((r[i]-l[i]+1)*height[i]));
        }
        return maxa;
    }
};

//algorithm2
//stack

 int largestRectangleArea(vector<int> &h) {
       stack<int> S;
       h.push_back(0);
       int sum = 0;
       for (int i = 0; i < h.size(); i++) {
            if (S.empty() || h[i] > h[S.top()]) S.push(i);
            else {
                 int tmp = S.top();
                 S.pop();
                 sum = max(sum, h[tmp]*(S.empty()? i : i-S.top()-1));
                 i--;
            }
       }
       return sum;
  }
