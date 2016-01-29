/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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
    TreeNode* sortedListToBST(ListNode* head) {
        // recursion: inorder traversal
        // time O(n), space O(n), O(logn) for recursion
        int len = 0; // size of list
        ListNode *p = head;
        while(p != nullptr) {
            p = p->next;
            len++;
        }
        ListNode *list = head;
        return sortedListToBST(0, len - 1, list);
    }
    
    TreeNode* sortedListToBST(int start, int end, ListNode* &list) { // reference of pointer here
        if (start > end) return nullptr;
        int mid = start + (end - start) / 2;
        TreeNode *left = sortedListToBST(start, mid - 1, list); // if not reference of pointer, list does not move here
        TreeNode *parent = new TreeNode(list->val);
        parent->left = left;
        list = list->next;
        parent->right = sortedListToBST(mid + 1, end, list);
        return parent;
    }
};