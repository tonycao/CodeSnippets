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
    bool isBalanced(TreeNode* root) {
        if (root == nullptr) return true;
        if (abs(maxheight(root->left) - maxheight(root->right)) > 1) return false;
        return isBalanced(root->left) && isBalanced(root->right);
        
        //return height(root) >= 0;
    }
    
    int maxheight(TreeNode *root) {
        if (root == nullptr) return 0;
        return max(maxheight(root->left), maxheight(root->right)) + 1;
    }
    
    int height(TreeNode* root) {
        if (root == nullptr) return 0;
        
        int left = height(root->left);
        int right = height(root->right);
        
        if (abs(left - right) > 1 || left == -1 || right == -1) return -1;
        
        return max(left, right) + 1;
    }
};