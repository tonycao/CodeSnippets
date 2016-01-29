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
    bool isValidBST(TreeNode* root) {
        // top-down recursion: Time ~ O(N), Space ~ O(logN) 
        //return valid(root, INT_MIN, false, INT_MAX, false);
        
       
        prev = nullptr;
        return valid2(root);
    }
    
private:
    TreeNode *prev;
    // min-max
    bool valid(TreeNode* node, int min, bool haslower, int max, bool hasupper) {
        if (node == nullptr) return true;
        return (!haslower || node->val > min) && (!hasupper || node->val < max) &&
            valid(node->left, min, haslower, node->val, true) &&
            valid(node->right, node->val, true, max, hasupper);
    }
    
    // inorder
    bool valid2(TreeNode* root) {
        if(root == nullptr) return true;
        
        if(valid2(root->left)) {
            if(prev && root->val <= prev->val) return false;
            prev = root;
            return valid2(root->right);
        }
        return false;
    }
    
};