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
    ListNode* reverseList(ListNode* head){
        if(head == NULL || head->next == NULL) return head;
        ListNode* tmphead = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return tmphead;
    }
    void reorderList(ListNode *head) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(head == NULL || head->next == NULL) return ;
        ListNode* slow = head;
        ListNode* fast = head;

        while(fast->next && fast->next->next){
            fast = fast->next->next;
            slow = slow->next;
            //if()
        }
        ListNode* head2 = slow->next;
        slow->next = NULL;
        head2 = reverseList(head2);
        ListNode* p1 = head;
        ListNode* p2 = head2;
        ListNode* tmp = NULL;

        while(p1 && p2){
            tmp = p1->next;
            p1->next = p2;
            p1 = tmp;
            tmp = p2->next;
            p2->next = p1;
            p2 = tmp;
        }
    }
};
