class Solution {
public:
    int longestValidParentheses(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> dp(s.size(),0);

        int max=0;

        for(int i=s.size()-2; i>=0; i--)
        {
            if(s[i]=='(')
            {
                int j=i+1+dp[i+1];
                if(j<s.size()&&s[j]==')')
                {
                    dp[i]=dp[i+1]+2;
                    if(j+1<s.size())
                    {
                        dp[i]+=dp[j+1];
                    }
                }

            }
            max= max>dp[i] ? max:dp[i];
        }
        return max;
    }
};
