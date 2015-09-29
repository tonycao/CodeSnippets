class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode* fast=head, *slow=head;
        for (int i = 0; i < n; i++) fast=fast->next;
        if (fast == NULL) return head->next;
        while(fast->next!=NULL){
            fast=fast->next;
            slow=slow->next;
        }
        slow->next = slow->next->next;
        return head;
    }

};
