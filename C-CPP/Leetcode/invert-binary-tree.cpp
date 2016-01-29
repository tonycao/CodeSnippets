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
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return root;
        /*
        //recursion: top down
        //Time ~ O(N), Space ~ O(N) 
        swap(root);
        invertTree(root->left);
        invertTree(root->right);
        
        // 
        */
        
        // recursion: bottom up
        // Time ~ O(N), Space ~ O(N) 
        invertTree(root->left);
        invertTree(root->right);
        swap(root);
        //root->left = right;
        //root->right = left;
        
        // dfs
        /*
        stack<TreeNode*> dfs;
        dfs.push(root);
        
        while(!dfs.empty()) {
            TreeNode* node = dfs.top();
            dfs.pop();
            TreeNode* tmp = node->left;
            node->left = node->right;
            node->right = tmp;
            if (node->right) dfs.push(node->right);
            if (node->left) dfs.push(node->left);
        }
        */
        
        // bfs
        /*
        queue<TreeNode*> bfs;
        bfs.push(root);
        while(!bfs.empty()) {
            TreeNode* node = bfs.front();
            bfs.pop();
            swap(node);
            if (node->left) bfs.push(node->left);
            if (node->right) bfs.push(node->right);
        }
        */
        return root;
    }
    
    void swap(TreeNode* node) {
        TreeNode* s = node->left;
        node->left = node->right;
        node->right = s;
    }
};