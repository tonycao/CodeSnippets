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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) return res;
         // method 1
        //postorder(root, res);
        //return res;
        
        // method 2 iterative
        stack<TreeNode*> stk;
        TreeNode* cur = root;
        TreeNode* prev = nullptr;
        while(cur || !stk.empty()) {
            if (cur) {
                stk.push(cur);
                cur = cur->left;
            } else {
                TreeNode* tmp = stk.top();
                if (tmp->right && prev != tmp->right) {
                    cur = tmp->right;
                } else {
                    res.push_back(tmp->val);
                    prev = tmp;
                    stk.pop();
                }
            }
        }
        return res;
    }
private:
    void postorder(TreeNode* root, vector<int> &res) {
        if (root == nullptr) return;
        postorder(root->left, res);
        postorder(root->right, res);
        res.push_back(root->val);
    }
};