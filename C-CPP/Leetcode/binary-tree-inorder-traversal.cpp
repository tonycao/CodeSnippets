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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) return res;
        // method 1: recursive
        //return inorder(root, res);
        
        // method 2: iterative
        /*
        stack<TreeNode*> stk;
        //stk.push(root);
        TreeNode* curNode = root;//->left;
        while (!stk.empty() || curNode != nullptr) {
            if (curNode != nullptr) {
                stk.push(curNode);
                curNode = curNode->left;
            } else {
                curNode = stk.top();
                stk.pop();
                res.push_back(curNode->val);
                curNode = curNode->right;
            }
        }
        return res;
        */
        // method 3: morris traversal
        
        return morrisInorder(root, res);
    }
    
private:
    vector<int> inorder(TreeNode* root, vector<int> &res) {
        if (root == nullptr) return res;
        inorder (root->left, res);
        res.push_back(root->val);
        inorder (root->right, res);
        return res;
    }
    
    vector<int> morrisInorder(TreeNode* root, vector<int> &res) {
        TreeNode *cur = root;
        while (cur) {
            // If left child is null, print the current node data. Move to
            // right child.
            if (cur->left == nullptr) {
                res.push_back(cur->val);
                //prev = cur;
                cur = cur->right;
            }
            else {
                // find inoder predecessor
                TreeNode *prev = cur->left;
                while (prev->right && prev->right != cur) 
                    prev = prev->right;
                
                // If the right child of inorder predecessor already points to
                // this node
                if (prev->right == cur) { // 左子树已遍历完，从左子节点回来
                    res.push_back(cur->val);
                    prev->right = nullptr;
                    cur = cur->right;
                } 
                // If right child doesn't point to this node, then print this
                // node and make right child point to this node
                else {
                    prev->right = cur;
                    cur = cur->left;
                }
            }
        }
        return res;
    }
};