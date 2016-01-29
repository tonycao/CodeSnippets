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
    vector<int> inorderTraversal2(TreeNode *root) {
        vector<int> res;
        if (root == nullptr) return res;
        
        return inorderTraversal(root, res);
    }
    
    // recursion
    vector<int> inorderTraversal(TreeNode *root, vector<int> &res) {
        if (root == nullptr) return res;
        
        inorderTraversal(root->left, res);
        res.push_back(root->val);
        inorderTraversal(root->right, res);
        return res;
    }
    
    //iterative
    vector<int> inorderTraversal(TreeNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<int> res;
        if (root == nullptr) return res;
        stack<TreeNode *> s;
        s.push(root);
        TreeNode *pNode = root->left;
        while(!s.empty() || pNode!=nullptr){
            if (pNode != nullptr) {
                s.push(pNode);
                pNode = pNode->left;
            } else {
                TreeNode *t = s.top();
                s.pop();
                res.push_back(t->val);
                pNode = t->right;
            }
        }
        return res;
    }
};