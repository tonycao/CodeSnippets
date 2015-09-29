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
    TreeNode *cbst(vector<int> &num, int st, int ed){
        if(st>ed) return NULL;
        else{
            int mid = (st+ed)/2;
            TreeNode *bst = new TreeNode(num[mid]);
            bst->left = cbst(num, st, mid-1);
            bst->right = cbst(num, mid+1,ed);
            return bst;
        }
    }

    TreeNode *sortedArrayToBST(vector<int> &num) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if (num.size() == 0) return NULL;
        return cbst(num, 0, num.size()-1);
    }
};
