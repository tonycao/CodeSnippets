/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
private:
    stack<TreeNode*> nodeStack;
public:
    BSTIterator(TreeNode *root) {
        while(root != nullptr) {
            nodeStack.push(root);
            root = root->left;
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !nodeStack.empty();
    }

    /** @return the next smallest number */
    int next() {
        int res = 0;
        if (!nodeStack.empty()) {
            TreeNode* cur = nodeStack.top();
            nodeStack.pop();
            res = cur->val;
            cur = cur->right;
            while(cur != NULL) {
                nodeStack.push(cur);
                cur = cur->left;
            }
        }
        return res;
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */