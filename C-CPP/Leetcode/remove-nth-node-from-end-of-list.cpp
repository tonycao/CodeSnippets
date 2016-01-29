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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // ListNode* dummy = new ListNode(-1); // use dummy to remove to handle 1 node case
        // dummy->next = head;
        // two pointers
        ListNode* fast = head, *slow = head; 
        while(n) {
            fast = fast->next;
            n--;
        }
        if (fast == nullptr) return head->next;
        while(fast->next) {
            fast = fast->next;
            slow = slow->next;
        }
        ListNode* tmp = slow->next;
        slow->next = slow->next->next;
        delete tmp;
        return head;
    }
};