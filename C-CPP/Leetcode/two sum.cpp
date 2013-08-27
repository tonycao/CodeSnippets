// Two Sum
class Solution{
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function

        vector<int> mul(numbers.size() , 0);
        vector<int> ans(2 , 0);
        map<int,int> mapping;

        for (int i=0; i<numbers.size(); ++i)
        {
            mul[i] = (target - numbers[i]) * numbers[i];

            if (mapping[mul[i]] > 0)
            {
                if (numbers[mapping[mul[i]]-1] + numbers[i]  == target)
                {
                    ans[0] = mapping[mul[i]];
                    ans[1] = i+1;
                    i = numbers.size();
                }
            }

            else
                mapping[mul[i]] = i+1;
        }

        return ans;
    }
};


// option 2
/*
class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> mul(numbers.size(), 0);
        vector<int> ans(2, 0);
        map<int,int> mapping;

        for (int i=0; i< numbers.size(); ++i){
            mul[i] = (target - numbers[i]); //*numbers[i];

            if (mapping[numbers[i]] > 0){
                if(numbers[mapping[numbers[i]]-1] + numbers[i] == target){
                    ans[0] = mapping[numbers[i]];
                    ans[1] = i+1;
                    i = numbers.size();
                }
            }
            else
                mapping[mul[i]] = i+1;
        }
        return ans;
    }
};
*/
