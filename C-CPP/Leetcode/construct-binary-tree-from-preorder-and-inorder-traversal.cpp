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
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        //return buildTree(begin(preorder), end(preorder), begin(inorder), end(inorder));
        return buildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }
private:   
    template<typename InputIterator>
    TreeNode *buildTree(InputIterator pre_first, InputIterator pre_last,
        InputIterator in_first, InputIterator in_last) {
        if (pre_first == pre_last) return nullptr;
        if (in_first == in_last) return nullptr;
        
        auto root = new TreeNode(*pre_first);
        
        auto in_root_pos = find(in_first, in_last, *pre_first);
        auto left_size = distance(in_first, in_root_pos);         // size of left subtree
        
        root->left = buildTree(next(pre_first), next(pre_first, 
            left_size + 1), in_first, in_root_pos);
        root->right = buildTree(next(pre_first, left_size + 1), 
            pre_last, next(in_root_pos), in_last);
        
        return root;
    }
    

    TreeNode* buildTree(vector<int> &preorder, int prestart, int preend, vector<int> &inorder, int instart, int inend) {
        if (instart > inend) return nullptr;
        if (prestart > preend) return nullptr;
        
        TreeNode *root = new TreeNode(preorder[prestart]);
        int position = findPosition(inorder, instart, inend, preorder[prestart]);
        
        root->left = buildTree(preorder, prestart + 1, prestart + (position - instart), inorder, instart, position - 1);
        //root->right = buildTree(preorder, position - inend + preend + 1, preend, inorder, position + 1, inend);
        root->right = buildTree(preorder, prestart + (position - instart) + 1, preend, inorder, position + 1, inend);
        return root;
    }
    
    int findPosition(vector<int> arr, int start, int end, int key) {
        for (int i = start; i <= end; i++) {
            if (arr[i] == key)
                return i;
        }
        return -1;
        
    }
};