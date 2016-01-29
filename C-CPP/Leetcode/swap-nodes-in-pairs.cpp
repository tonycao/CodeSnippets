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
    ListNode* swapPairs(ListNode* head) {
        // method 1
        /*
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;
        
        ListNode *prev = dummy, *cur = head;
        while(cur && cur->next) {
            ListNode *tmp = cur->next->next;
            cur->next->next = prev->next;
            prev->next = cur->next;
            cur->next = tmp;
            
            prev = cur;
            cur = cur->next;
        }
        head = dummy->next;
        delete dummy;
        return head;
        */
        
        // method 2: pointer to pointer
        // https://leetcode.com/discuss/46090/7-8-lines-c-python-ruby
        /*
        ListNode **pp = &head, *a, *b;
        while((a = *pp) && (b = a->next)) {
            a->next = b->next;
            b->next = a;
            *pp = b;
            pp = &(a->next);
        }
        return head;
        */
        
        // method 3: recursion
        if (head == nullptr || head->next == nullptr) return head;
        
        ListNode *newhead = head->next;
        head->next = swapPairs(newhead->next);
        newhead->next = head;
        return newhead;
    }
};