/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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
    TreeNode *sortedListToBST(ListNode *head) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int len = 0;
        ListNode *p = head;
        while(p){
            len++;
            p = p->next;
        }
        //int start = 0;
        //int end = len-1;
        return sortedListToBST(head, 0, len-1);
    }

    TreeNode *sortedListToBST(ListNode *&list, int start, int end){
        if(start > end) return NULL;
        int mid = start + (end-start)/2;
        TreeNode *leftChild = sortedListToBST(list, start, mid-1);
        TreeNode *parent = new TreeNode(list->val);
        parent->left = leftChild;
        list = list->next;
        parent->right = sortedListToBST(list, mid+1, end);
        return parent;

    }
};
