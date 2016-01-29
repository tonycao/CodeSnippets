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
        //DFS: Time ~ O(logN), Space ~ O(logN)
        /*/ recursive
        if (root->val > p->val && root->val > q->val) return lowestCommonAncestor(root->left, p, q);
        else if (root->val < p->val && root->val < q->val) return lowestCommonAncestor(root->right, p, q);
        
        else return root;
        */
        
        // iterative
        while(root) {
            if (root->val > p->val && root->val > q->val) 
                root = root->left;
            else if (root->val < p->val && root->val < q->val) 
                root = root->right;
            else
                break;
        }
        return root;
    }
};