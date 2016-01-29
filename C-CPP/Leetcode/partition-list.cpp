/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode *less = new ListNode(-1);
        ListNode *greater = new ListNode(-1);
        ListNode *curless = less, *curgreater = greater;
        ListNode *cur = head;
        while(cur) {
            if (cur->val < x) {
                curless->next = cur;
                curless = cur;
            } else {
                curgreater->next = cur;
                curgreater = cur;
            }
            cur = cur->next;
        }
        curless->next = greater->next;
        curgreater->next = nullptr;     // do not forget this step
        delete greater;
        head = less->next;
        delete less;
        return head;
    }
};