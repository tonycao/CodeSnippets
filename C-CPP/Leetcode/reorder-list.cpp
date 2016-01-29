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
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return ;
        ListNode *slow = head, *fast = head, *prev = nullptr;
        while(fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // reverse the second half
        prev->next = nullptr;
        slow = reverse(slow);
        
        // merge
        ListNode *cur = head;
        while(cur && slow) {
            ListNode *tmp = cur->next;
            cur->next = slow;
            cur = cur->next;
            slow = tmp;
        }
        //cur->next = slow;
    }
    
    ListNode *reverse(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode *cur = head, *prev = nullptr;
        
        while(cur) {
            ListNode *tmp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = tmp;
        }
        return prev;
    }
};