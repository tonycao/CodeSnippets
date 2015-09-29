class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
                int n = matrix.size();
        for (int layer=0; layer<n/2; layer++){
            int first = layer;
            int last  = n-1-layer;
            for (int i=first;i<last;i++){
                int offset = i-first;
                int top = matrix[first][i];
                //left->top
                matrix[first][i]=matrix[last-offset][first];
                //bottom->top
                matrix[last-offset][first] = matrix[last][last-offset];
                //right->bottom
                matrix[last][last-offset] = matrix[i][last];
                //top->right
                matrix[i][last] = top;
            }
        }
    }
};

//alogrithm 2

void rotate(vector<vector<int> > &matrix) {
     // Start typing your C/C++ solution below
      // DO NOT write int main() function
      int len = matrix[0].size();
      for(int i =0; i<len-1; i++)
      {
        for(int j=0;j<len-i;j++)
        {
          swap(matrix[i][j], matrix[len-1-j][len-1-i]);
        }
      }
      for(int i =0; i<len/2; i++)
      {
        for(int j=0;j<len;j++)
        {
          swap(matrix[i][j], matrix[len-i-1][j]);
        }
      }
    }
    void swap(int& a1, int&a2)
    {
      int temp = a1;
      a1=a2;
      a2=temp;
    }
