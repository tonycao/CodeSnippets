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
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        vector<int> cur;
        findPathSum(root, sum, cur, res);
        return res;
    }
    //DFS
    void findPathSum(TreeNode *root, int sum ,vector<int> &cur, vector<vector<int>> &res) {
        if (root == nullptr) return;
        cur.push_back(root->val);
        if (root->left == nullptr && root->right == nullptr) {
            if (sum == root->val) res.push_back(cur);
        }
        
        findPathSum(root->left, sum - root->val, cur, res);
        findPathSum(root->right, sum - root->val, cur, res);
        
        cur.pop_back();
    } 
};