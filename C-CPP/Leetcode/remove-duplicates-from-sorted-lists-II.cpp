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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode *prev = dummy, *cur = head;
        
        while(cur != nullptr && cur->next != nullptr) {
            if (cur->val != cur->next->val) {
                prev = cur;
            } else {
                while(cur->next != nullptr &&  cur->val == cur->next->val) {
                    cur = cur->next;
                }
                prev->next = cur->next;
            }
            cur = cur->next;
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};