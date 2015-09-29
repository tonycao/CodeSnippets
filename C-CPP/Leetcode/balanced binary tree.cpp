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

    int maxDepth(TreeNode *root){
        if(root == NULL) return 0;
        return 1+max(maxDepth(root->left),maxDepth(root->right));
    }

    bool testNode(TreeNode *root){
        if(root == NULL) return true;
        if(abs(maxDepth(root->left)-maxDepth(root->right))>1) return false;
        return (testNode(root->left) && testNode(root->right));
    }

    bool isBalanced(TreeNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        return testNode(root);
    }
};
