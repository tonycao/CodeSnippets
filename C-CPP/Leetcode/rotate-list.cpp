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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr || k <= 0) return head;
        ListNode* cur = head; //, *prev = head;
        
        // compute length
        int len = 1;
        while(cur->next != nullptr) {
            cur = cur->next;
            len++;
        }
        
        // compute steps
        k = k % len;
        int step = len - k;
        
        // rotate
        cur->next = head;
        while(step) {
            cur = cur->next;
            step--;
        }
        
        ListNode* dummy = cur->next;
        cur->next = nullptr;
        //cur->next = head;
        return dummy;
    }
};