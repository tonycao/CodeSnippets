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
    int kthSmallest(TreeNode* root, int k) {
        int res;
        // inorder traversal: recursive
        //inorder(root, k, res);
        // iterative
        
        /*stack<TreeNode*> s;
        int rank = 1;
        while(!s.empty() || root) {
            while(root) {
                s.push(root);
                root = root->left;
            }
            
            root = s.top()->right;
            if (rank == k) return s.top()->val;
            s.pop();
            rank++;
        }
        
        return INT_MAX; */
        //return res;
        
        
        // binary search
        int n = size(root->left);
        if (n + 1 == k) return root->val;
        else if (n + 1 < k) return kthSmallest(root->right, k - n - 1);
        else return kthSmallest(root->left, k);
        
    }
    
private:
    int size(TreeNode* root) {
        if (root == nullptr) return 0;
        return size(root->left) + size(root->right) + 1;
    }
    
    void inorder(TreeNode* root, int &k, int &res) {
        if (root == nullptr) return ;
        inorder(root->left, k, res);
        if (!--k){ 
            res = root->val;
            return;
        }
        inorder(root->right, k, res);
    }
};