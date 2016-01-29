/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int maxsum = INT_MIN; // store the max at current node
        dfs(root, maxsum);
        return maxsum;
    }
    
    int dfs(TreeNode *root, int &maxsum) {
        if (!root) return 0;
        int l = dfs(root->left, maxsum);
        int r = dfs(root->right, maxsum);
        
        int m = root->val;
        if (l > 0) m += l;
        if (r > 0) m += r;
        
        maxsum = max(m, maxsum);
        
        return max(l, r) > 0 ? max(l, r) + root->val : root->val;
    }
};