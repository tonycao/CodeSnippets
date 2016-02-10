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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) return res;
        // method 1: time~O(N), space~O(logN)
        //preorder(root, res);
        //return res;
        
        // method 2:iterative time~O(N), space~O(N) ?
        /*
        stack<TreeNode*> stk;
        stk.push(root);
        while (!stk.empty()) {
            TreeNode *tmp = stk.top();
            stk.pop();
            if (tmp->right) stk.push(tmp->right);
            if (tmp->left) stk.push(tmp->left);
            res.push_back(tmp->val);
        }
        return res;
        */
        
        // method 3: morris 
        return morrisPreorder(root, res);
    }
    
private:
    void preorder(TreeNode* root, vector<int> &res) {
        if (root == nullptr) return ;
        res.push_back(root->val);
        preorder(root->left, res);
        preorder(root->right, res);
    }
    
    vector<int> morrisPreorder(TreeNode* root, vector<int> &res) {
        TreeNode *cur = root, *prev;
        
        while (cur) {
            // If left child is null, print the current node data. Move to
            // right child.
            if (cur->left == nullptr) {
                res.push_back(cur->val);
                cur = cur->right;
            } else {
                // Find inorder predecessor 寻找该节点的前序节点
                prev = cur->left;
                while (prev->right && prev->right != cur) {
                    prev = prev->right;
                }
                
                // If the right child of inorder predecessor already points to
                // this node
                if (prev->right == cur) // 左子树已遍历完，从左子节点回来
                {
                    prev->right = nullptr;
                    cur = cur->right;
                }
                
                // If right child doesn't point to this node, then print this
                // node and make right child point to this node
                else {
                    res.push_back(cur->val);
                    prev->right = cur;
                    cur = cur->left;
                }
            }
        }
        return res;
    }
};