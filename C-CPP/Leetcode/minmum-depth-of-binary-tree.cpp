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
    int minDepth(TreeNode* root) {
        /*
        if (root == NULL) return 0;
        int left = minDepth(root->left);
        int right = minDepth(root->right);
        if (left == 0 && right == 0) return 1;
        if (left == 0) left = INT_MAX;
        if (right == 0) right = INT_MAX;
        return min(left, right) + 1;
        */
        
        // recursive
        // DFS: Time ~ O(N), Space ~ O(logN)
        //*
        if (root == nullptr) return 0;
        if (root->left == nullptr)
            return minDepth(root->right) + 1;
        else if (root->right == nullptr)
            return minDepth(root->left) + 1;
        else 
            return min(minDepth(root->left), minDepth(root->right)) + 1;
        //*/
        
        // iterative
        /*
        //BFS: Time ~ O(N), Space ~ O(logN) 
        //记录每层最右node为rightMost，每当碰到rightMost且其下仍有子树，则depth加1。
        //当某个节点的左右子树都为空，即结束返回depth。
        if (root == nullptr) return 0;
        queue<TreeNode *> q;
        q.push(root);
        TreeNode *rightmost = root;
        int depth = 1;
        while(!q.empty()) {
            
            TreeNode *tmp = q.front();
            q.pop();
            if (tmp->left == nullptr && tmp->right == nullptr) break; // stop
            if (tmp->left != nullptr) q.push(root->left);
            if (tmp->right != nullptr) q.push(root->right);
            if (tmp == rightmost) {
                depth++;
                rightmost = (tmp->right != nullptr) ? tmp->right : tmp->left;
            }
        }
        return depth;
        */
    }
};