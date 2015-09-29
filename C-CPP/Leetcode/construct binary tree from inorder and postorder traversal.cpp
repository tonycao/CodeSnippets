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

    TreeNode *ct(vector<int> &inorder, vector<int> &postorder, int ist, int ied, int ped){
        if(ist>ied) return NULL;
        TreeNode *res = new TreeNode(postorder[ped]);
        int mid;
        for(int i = ist; i<=ied; i++){
            if(inorder[i] == res->val){
                mid = i; break;
            }
        }
        res->right = ct(inorder, postorder, mid+1, ied, ped-1);
        res->left = ct(inorder, postorder, ist, mid-1, ped-1-ied+mid);
        return res;
    }

    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(postorder.size()==0){return NULL;}
        else{
            return ct(inorder, postorder, 0, inorder.size()-1, postorder.size()-1);
        }
    }
};
