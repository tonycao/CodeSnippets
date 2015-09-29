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

    int max_s;
    int dfs(TreeNode *root){
        if(!root) return 0;
        int l = dfs(root->left);
        int r = dfs(root->right);
        int m = root->val;
        if(l>0) m+=l;
        if(r>0) m+=r;

        max_s = max(max_s, m);
        if(max(l,r) > 0) return (max(l,r)+root->val);
        else return root->val;
    }

    int maxPathSum(TreeNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        max_s = INT_MIN;
        dfs(root);
        return max_s;
    }
};
