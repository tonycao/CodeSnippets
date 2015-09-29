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
    vector<vector<int> > levelOrder(TreeNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        queue<TreeNode*> q1,q2;
        vector<vector<int> > res;
        if (root!=NULL){
            q1.push(root);
            vector<int> lres;
            TreeNode *cnode;
            while (true) {
                while (!q1.empty()){ //save one level
                    cnode =q1.front();
                    q1.pop();
                    if (cnode->left!=NULL){q2.push(cnode->left);}
                    if (cnode->right!=NULL){q2.push(cnode->right);}
                    lres.push_back(cnode->val);
                }
                res.push_back(lres);
                lres.clear();
                q1 = q2;
                while (!q2.empty()) {q2.pop();}
                if (q1.empty()){return res;}
            }
        }
        return res;
    }
};
