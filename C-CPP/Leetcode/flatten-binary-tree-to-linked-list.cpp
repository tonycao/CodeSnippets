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
    void flatten(TreeNode* root) {
        if (root == nullptr) return;
        //http://wlcoding.blogspot.com/2015/02/flatten-binary-tree-to-linked-list_44.html?view=sidebar
        // recursive: Time ~ O(N), Space ~ O(logN) 
        /*
        flatten(root->left);
        flatten(root->right);
        
        if (root->left == nullptr) return ;
        
        // merge: root->left->right
        TreeNode* p = root->left;
        while(p->right) p = p->right; // find right most node
        p->right = root->right;
        root->right = root->left;
        root->left = nullptr;
        */
        
        // iterative: Time ~ O(N), Space ~ O(1) 
        TreeNode *cur = root;
        while(cur != nullptr) {
            if (cur->left != nullptr) {
                //if (cur->right != nullptr) {
                    TreeNode *next = cur->left;
                    while(next->right != nullptr) next = next->right;
                    next->right = cur->right;
                //}
                
                cur->right = cur->left;
                cur->left = nullptr;
            }
            cur = cur->right;
        }
    }
};