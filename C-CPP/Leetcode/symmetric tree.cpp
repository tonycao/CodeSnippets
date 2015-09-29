/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    // recursive
    bool isSymm(TreeNode *a, TreeNode *b){
        if(a == NULL) return b==NULL;
        if(b == NULL) return false;
        if(a->val!=b->val) return false;
        if(!isSymm(a->left, b->right)) return false;
        if(!isSymm(a->right, b->left)) return false;
        return true;
    }
    bool isSymmetric(TreeNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(root == NULL) return true;
        return isSymm(root->left, root->right);
    }
};

// iterative
bool isSymmetric(TreeNode *root) {
      // Start typing your C/C++ solution below
      // DO NOT write int main() function
      if(root == NULL) return true;
      vector<TreeNode*> preLevel;
      vector<TreeNode*> curLevel;
      preLevel.push_back(root);
     while(preLevel.size()>0)
      {
        while(preLevel.size()>0)
        {
          TreeNode *p = preLevel.back();
         preLevel.pop_back();
         if(p == NULL) continue;
         curLevel.push_back(p->left);
          curLevel.push_back(p->right);
        }
        int start = 0, end = curLevel.size()-1;
       while(start< end)
        {
          TreeNode *pl = curLevel[start];
          TreeNode *pr = curLevel[end];
          int l = pl== NULL? -1:pl->val;
          int r = pr== NULL? -1: pr->val;
          if(l!=r)
            return false;
         start++;
          end--;
        }
       preLevel.clear();
        preLevel.insert(preLevel.begin(), curLevel.begin(), curLevel.end());
        curLevel.clear();
      }
      return true;
   }



