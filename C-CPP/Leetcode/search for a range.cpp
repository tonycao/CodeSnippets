class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> res(2,-1);
        if(n == 0) return res;
        res[0]=searchMaxLessThan(A,target,0,n-1);
        res[1]=searchMaxLessThan(A,target+1,0,n-1);
        if(res[0]==res[1]){
            res[0]=-1;
            res[1]=-1;
        }else{
            res[0]++;
        }
        return res;
    }

    int searchMaxLessThan(int A[], int target, int start, int end){
        if(start==end) return A[start]<target?start:start-1;
        if(start==end-1) return A[end]<target?end:(A[start]<target?start:start-1);
        int mid = (start+end)/2;
        if(A[mid]>=target){
            end=mid-1;
        }else{
            start=mid;
        }
        return searchMaxLessThan(A,target,start,end);
    }
};
