/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (root == nullptr) return;
        // dummy is the node above curr
        // dummy.next stores the leftmost node in the next level
        TreeLinkNode *dummy = new TreeLinkNode(-1);
        TreeLinkNode *prev = dummy, *cur = root;
        while(cur) {
            // when curr has any child:
            // if it's the leftmost node, connect dummy.next to it 
            // otherwise. connect previous left node to it
            if (cur->left != nullptr) {
                prev->next = cur->left;
                prev = prev->next;
            }
            if (cur->right != nullptr) {
                prev->next = cur->right;
                prev = prev->next;
            }
            cur = cur->next;
        }
        connect(dummy->next);
    }
};