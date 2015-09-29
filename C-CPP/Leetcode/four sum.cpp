class Solution {
public:
    vector<vector<int> > fourSum(vector<int> &num, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int nSize = num.size();
        vector< vector<int> > result;
        if (nSize < 4) return result;

        sort(num.begin(), num.end());
        vector<int> mid(4);
        set<string> isExit;
        for (int i = 0; i < nSize - 3; ++i)
        {
            mid[0] = num[i];
            for (int j = i + 1; j < nSize - 2; ++j)
            {
                mid[1] = num[j];
                int l = j + 1;
                int r = nSize - 1;
                int sum = target - num[i] - num[j];
                while(l < r)
                {
                    int tmp = num[l] + num[r];
                    if (sum == tmp)
                    {
                        string str;
                        str += num[i];
                        str += num[j];
                        str += num[l];
                        str += num[r];
                        set<string>::iterator itr = isExit.find(str);
                        if (itr == isExit.end())
                        {
                            isExit.insert(str);
                            mid[2] = num[l];
                            mid[3] = num[r];
                            result.push_back(mid);
                        }
                        ++l;
                        --r;
                    }
                    else if(sum > tmp)
                        ++l;
                    else
                        --r;
                }
            }
        }

        return result;
    }
};
