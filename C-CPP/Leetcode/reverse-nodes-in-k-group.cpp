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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(head == nullptr || k == 1) return head;
        
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;
        ListNode *prev = dummy, *cur = head;
        int pos = 0;
        while(cur != nullptr) {
            pos++;
            if (pos % k == 0) {
                prev = reverse(prev, cur->next);
                cur = prev->next;
            } else {
                cur = cur->next;
            }
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
    
    ListNode *reverse(ListNode *prev, ListNode *next) {
        ListNode *last = prev->next, *cur = last->next;
        while(cur != next) {
            last->next = cur->next;
            cur->next = prev->next;
            prev->next = cur;
            cur = last->next;
        }
        return last;
    }
};