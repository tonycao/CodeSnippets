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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> res;
        // recursive
        traverse(root, 1, res);
        reverse(res.begin(), res.end());
        return res;
        
        
        
        //iterative with queue
        /*
        
        if (root == nullptr) return res;
        
        queue<TreeNode *> cur, next;
        vector<int> level;
        cur.push(root);
        while(!cur.empty()) {
            level.clear();
            while(!cur.empty()) {
                TreeNode *node = cur.front();
                cur.pop();
                level.push_back(node->val);
                if (node->left != nullptr) next.push(node->left);
                if (node->right != nullptr) next.push(node->right);
            }
            res.push_back(level);
            swap(next, cur);
        }
        
        reverse(res.begin(), res.end());
        return res;
        */
    }
    
    void traverse(TreeNode *root, int level, vector<vector<int>> &res) {
        if (root == nullptr) return;
        if (level > res.size()) res.push_back(vector<int>());
        
        res[level - 1].push_back(root->val);
        traverse(root->left, level + 1, res);
        traverse(root->right, level + 1, res);
    }
};