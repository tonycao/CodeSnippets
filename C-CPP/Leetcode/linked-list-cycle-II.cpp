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
    ListNode *detectCycle(ListNode *head) {
        ListNode *fast = head, *slow = head;
        while(fast && fast->next) {
            
            slow = slow->next;
            fast = fast->next->next;
            // after slow met fast, let fast be head then proceed fast and slow together until they meet with each other
            if (slow == fast) {
                fast = head;
                while(fast != slow) {
                    
                    fast = fast->next;
                    slow = slow->next;
                }
                return fast;
            }
        }
        return NULL;
    }
};