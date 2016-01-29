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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (root == nullptr) return res;
        
        queue<TreeNode*> q;
        bool left_to_right = true;   // left to right
        vector<int> level;
        
        q.push(root);
        q.push(nullptr); // seperate each level
        
        while(!q.empty()) {
            TreeNode *cur = q.front();
            q.pop();
            if (cur) {
                level.push_back(cur->val);
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            } else {
                if (left_to_right) {
                    res.push_back(level);
                } else {
                    reverse(level.begin(), level.end());
                    res.push_back(level);
                }
                left_to_right = !left_to_right;
                level.clear();
                if (!q.empty()) q.push(nullptr);
                
            }
        }
        return res;
    }
};