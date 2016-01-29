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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (root == nullptr) return res;
        traversal(root, 1, res);
        // iterative
        /*
        
        queue<TreeNode*> current, next;
        current.push(root);
        vector<int> level;
        while(!current.empty()) {
            while(!current.empty()) {
                TreeNode* tmp = current.front();
                current.pop();
                level.push_back(tmp->val);
                if (tmp->left != nullptr) next.push(tmp->left);
                if (tmp->right != nullptr) next.push(tmp->right);
            }
            res.push_back(level);
            swap(current, next);
            level.clear();
        }
        */
        
        return res;
    }
    
    // recursive
    void traversal(TreeNode *root, int level, vector<vector<int>> &result) {
        if (!root) return ;
        if (level > result.size())
            result.push_back(vector<int>());
            
        result[level-1].push_back(root->val);
        traversal(root->left, level+1, result);
        traversal(root->right, level+1, result);
    }
    
};