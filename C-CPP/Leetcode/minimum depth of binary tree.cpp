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
    int minDepth(TreeNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(root == NULL) return 0;
        int leftdep = minDepth(root->left);
        int rightdep = minDepth(root->right);
        if(leftdep == 0 && rightdep == 0) return 1;
        if(leftdep == 0) leftdep = INT_MAX;
        if(rightdep == 0) rightdep = INT_MAX;
        return 1+min(leftdep, rightdep);
    }
};
