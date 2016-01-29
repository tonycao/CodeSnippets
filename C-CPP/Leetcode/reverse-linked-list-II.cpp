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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;
        
        ListNode *prev = dummy;
        for (int i = 0; i < m-1; i++) {   // m - 1
            prev = prev->next;
        }
        ListNode *cur = prev->next;
        for (int i = 0; i < n - m; i++) {
            ListNode* move = cur->next;
            cur->next = move->next;
            move->next = prev->next; 
            prev->next = move;
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};