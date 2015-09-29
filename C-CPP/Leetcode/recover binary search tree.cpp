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
    TreeNode *first;
    TreeNode *second;
    TreeNode *pre;

    void inOrder(TreeNode *root){
        if (root==NULL){return;}
        else{
            inOrder(root->left);
            if (pre == NULL){pre = root;}
            else {
                if (pre->val > root->val){
                    if (first==NULL) {first = pre;}
                    second = root;
                }
                pre = root;
            }
            inOrder(root->right);

        }
    }
    void recoverTree(TreeNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        pre = NULL;
        first = NULL;
        second= NULL;
        inOrder(root);
        int val;
        val = first->val;
        first->val=second->val;
        second->val=val;
        return;
    }
};
