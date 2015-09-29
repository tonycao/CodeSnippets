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

    void flatbt(TreeNode *r, vector<int> &l){
        if(r == NULL) return ;
        l.push_back(r->val);
        flatbt(r->left, l);
        flatbt(r->right, l);
    }

    void flatten(TreeNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(root == NULL) return;
        vector<int> l;
        flatbt(root, l);
        TreeNode *head = root;
        for(int i = 1; i < l.size(); i++){
            head->right = new TreeNode(l[i]);
            head->left = NULL;
            head = head->right;
        }
        return;
    }
};
