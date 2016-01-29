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
    vector<int> preorder(TreeNode *root, vector<int> &res){
        if(!root) return res;
        res.push_back(root->val);
        preorder(root->left, res);
        preorder(root->right, res);
        return res;
    }
    vector<int> preorderTraversal(TreeNode *root) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<int> res;
        // method 1: recursive, Time ~ O(N), Space ~ O(logN)
        //return preorder(root, res);
        
        // method 3: stack
        stack<TreeNode*> nodeStack;
        TreeNode* curr = root;
        
        if (curr != nullptr) nodeStack.push(curr);
        
        while(!nodeStack.empty()) {
            curr = nodeStack.top();
            nodeStack.pop();
            res.push_back(curr->val);

            if (curr->right != nullptr) nodeStack.push(curr->right);
            if (curr->left != nullptr) nodeStack.push(curr->left);
        }
        
        return res;
    }
};