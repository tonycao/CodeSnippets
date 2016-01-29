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
    vector<int> rightSideView(TreeNode* root) {
        //Level-order Traversal: Time ~ O(N), Space ~ O(N) 
        vector<int> res;
        if (root == nullptr) return res;
        queue<TreeNode*> curlevel;
        
        curlevel.push(root);
        curlevel.push(nullptr);
        
        while(!curlevel.empty()) {
            TreeNode* cur = curlevel.front();
            curlevel.pop();
            while(cur != nullptr) {
                if (cur->left != nullptr) curlevel.push(cur->left);
                if (cur->right != nullptr) curlevel.push(cur->right);
                if (curlevel.front() == nullptr) res.push_back(cur->val); // last node at current level
                cur = curlevel.front();
                curlevel.pop();
            }
            if (!curlevel.empty()) curlevel.push(nullptr);
        }
        return res;
    }
};