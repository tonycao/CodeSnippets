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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        // DFS: Time~O(N), space~O(N)
        //Recursively search for p an q from bottom up, return p or q if founded, otherwise return null.
        //If left and right both return null (both left and right subtree doesn't contain p and q), then return null;
        //If left returns p or q (left subtree contain p or q) and right returns null (right subtree doesn't contain p and q), then return left;
        //If right returns p or q (right subtree contains p or q) and left returns null (left subtree doesn't contain p and q), then return right;
        //If both left and right return p or q (both left and right subtree contains p or q), then the root is the LCA.
        
        if (root == nullptr || p == nullptr || q == nullptr) return nullptr;
        if (root == p || root == q) return root; // duplicate allowed so compare the value is not enough
        
        // 1. recursive bottom-up
        /*
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        
        if (left && right) return root;
        return (left) ? left : right;
        */
        
        // 2. recursive top-down
        int totalMatches = countMatches(root->left, p, q);
        if (totalMatches == 1) return root;
        else if (totalMatches == 2) return lowestCommonAncestor(root->left, p, q);
        else return lowestCommonAncestor(root->right, p, q);
        
        
    }
    
    
    int countMatches(TreeNode* root, TreeNode *p, TreeNode *q) {
        if (root == nullptr) return 0;
        int matches = countMatches(root->left, p, q) + countMatches(root->right, p, q);
        if (root == p || root == q) return 1 + matches;
        else return matches;
    }
};