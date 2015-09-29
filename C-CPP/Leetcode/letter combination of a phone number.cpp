  #include <iostream>
  #include <vector>
  #include <string>

  using namespace std;

class Solution {
public:

    void findpath(string &digits, int level, string &path, vector<string> &res, vector<string> &v){

       if(level == digits.length()) {
          res.push_back(path);
          return;
       }
       int num = digits[level] - '0';
      if(num == 1 || num == 0) findpath(digits,level+1,path,res,v);
      else{
         for(int i = 0; i < v[num].length(); i++){
          path.push_back(v[num][i]);
          findpath(digits,level+1,path,res,v);
          path.pop_back();
        }
      }
    }
    vector<string> letterCombinations(string digits) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<string> res;
       string path;
       vector<string> v(10);
       v[2] = "abc";
       v[3] = "def";
       v[4] = "ghi";
       v[5] = "jkl";
       v[6] = "mno";
       v[7] = "pqrs";
       v[8] = "tuv";
       v[9] = "wxyz";
       findpath(digits, 0, path, res, v);

       return res;
    }
};

