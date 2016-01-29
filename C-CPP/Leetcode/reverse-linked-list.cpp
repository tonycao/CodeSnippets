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
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        
        /*// iterative
        ListNode *prev = nullptr;
        ListNode *cur = head;
        while(cur) {
            ListNode *next = cur->next; // save the next node
            cur->next = prev;           // invert current pointer
            prev = cur;                 // move forward
            cur = next;                
        }
        return prev;
        */
        
        
        
       
        
        //*/recursive
        ListNode *next = head->next; 
        ListNode *newHead = reverseList(next);  // get the last node of the list
        next->next = head;           // invert the pointer
        head->next = nullptr;        //   
        return newHead;
        //*/
    }
};