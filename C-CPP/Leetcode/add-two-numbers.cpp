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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *dummy = new ListNode(-1), *cur = dummy;
        int carry = 0;
        ListNode *curl1 = l1, *curl2 = l2;
        while(curl1 || curl2) {
            int sum = (curl1 ? curl1->val : 0) + (curl2 ? curl2->val : 0) + carry;
            cur->next = new ListNode(sum % 10);
            carry = sum / 10;
            cur = cur->next;
            if (curl1) curl1 = curl1->next;
            if (curl2) curl2 = curl2->next;
        }
        if (carry > 0) cur->next = new ListNode(carry);
        cur = dummy->next;
        delete dummy;
        return cur;
    }
};