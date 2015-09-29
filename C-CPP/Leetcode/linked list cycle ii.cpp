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
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(!head) return NULL;
        ListNode *fast = head;
        ListNode *slow = head;

        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast){
                ListNode *slow2 = head;
                if(slow2 == slow) return slow2;
                else{
                    while(slow2 != slow){
                        slow2 = slow2->next;
                        slow = slow->next;
                    }
                    return slow2;
                }
            }
        }
        return NULL;
    }
};
