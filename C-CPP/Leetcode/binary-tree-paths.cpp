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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
        if (root == nullptr) return res;
        
        // recursive
        //binaryTreePaths(root, res, to_string(root->val));
        
        // iterative
        vector<int> pathVal({root->val});
        
        // used for dfs
        stack<TreeNode*> st;
        vector<TreeNode*> path;
        st.push(root);
        TreeNode *curr, *pre = nullptr;
        while(!st.empty()) {
            curr = st.top();
            if ((curr->left == nullptr && curr->right == nullptr) || (pre != nullptr && 
                (curr->left == pre || curr->right == pre))) {
                st.pop();
                if (curr->left == nullptr && curr->right == nullptr) {
                    path.push_back(curr);
                    res.push_back(printPath(path));
                }
                path.pop_back();
                pre = curr;
            } else {
                if (curr->right != nullptr) st.push(curr->right);
                if (curr->left != nullptr) st.push(curr->left);
                path.push_back(curr);
            }
        }
        
        
        
        return res;
    }
    
private:
    // recursive: pre-order traversal
    void binaryTreePaths(TreeNode* root, vector<string> &res, string str) {

        if (root->left == nullptr && root->right == nullptr) { // child node
            res.push_back(str);
            return;
        } 
        
        if (root->left)
            binaryTreePaths(root->left, res, str + "->" + to_string(root->left->val));
        if (root->right)
            binaryTreePaths(root->right, res, str + "->" + to_string(root->right->val));
    }
    
    string printPath(vector<TreeNode*> path) {
        string p;
        for (int i = 0; i < path.size(); i++) {
            if (i == 0) p += to_string(path[i]->val);
            else {
                p += "->" + to_string(path[i]->val);
            }
        }
        return p;
    }
};