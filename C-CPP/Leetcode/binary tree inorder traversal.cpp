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
    void inOrder(TreeNode *root, vector<int> &res){
        if(root != NULL){
            inOrder(root->left, res);
            res.push_back(root->val);
            inOrder(root->right, res);
        }
    }
    vector<int> inorderTraversal(TreeNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<int> res;
        inOrder(root, res);
        return res;
    }
};
