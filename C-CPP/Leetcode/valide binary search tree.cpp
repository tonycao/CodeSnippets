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

    void inorder(TreeNode *root, bool &flag, int &pre){
        if(!root || !flag){
            return;
        }else{
            inorder(root->left, flag, pre);
            if(pre==-1) pre = root->val;
            else{
                if(pre>=root->val){
                    flag = false;
                    return ;
                }
                pre = root ->val;
            }
            inorder(root->right, flag, pre);
        }
    }
    bool isValidBST(TreeNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(!root) return true;
        bool flag = true;
        int pre = -1;
        inorder(root, flag, pre);
        return flag;
    }
};


//algorithm 2
bool isValidBST(TreeNode *root) {
    return IsValidBST(root, INT_MIN, INT_MAX);
}

bool IsValidBST(TreeNode* node, int MIN, int MAX)
{
    if(node == NULL)
        return true;
    if(node->val > MIN
            && node->val < MAX
            && IsValidBST(node->left,MIN,node->val)
            && IsValidBST(node->right,node->val,MAX))
        return true;
    else
        return false;
}
