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
    TreeNode *ct(vector<int> &preorder, vector<int> &inorder, int ist, int ied, int pst){
        if(ist > ied) return NULL;
        TreeNode *res = new TreeNode(preorder[pst]);
        int mid;
        for(int i = ist; i <= ied; i++){
            if(inorder[i] == res->val){
                mid = i;
                break;
            }
        }
        res->right = ct(preorder, inorder, mid+1, ied, pst+1+mid-ist);
        res->left = ct(preorder, inorder, ist, mid-1, pst+1);
        return res;
    }
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if (preorder.size() == 0){
            return NULL;
        }else{
            return ct(preorder, inorder, 0, inorder.size()-1,0);
        }
    }
};
