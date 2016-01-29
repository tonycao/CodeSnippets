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
    int sumNumbers(TreeNode* root) {
        // dfs
        return dfs(root, 0);
    }
    
    private:
    int dfs(TreeNode* root, int sum) {
        if (root == nullptr) return 0;
        
        sum = sum * 10 + root->val;
        if (root->left == nullptr && root->right == nullptr) return sum; // leaf node
        return dfs(root->left, sum) + dfs(root->right, sum);
    }
};