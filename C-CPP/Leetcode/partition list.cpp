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
    ListNode *partition(ListNode *head, int x) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if (head == NULL || head->next == NULL) return head;
        ListNode *p = new ListNode(0);
        p->next = head;
        head = p;
        ListNode *last = head;
        int n = 0;

        while(last->next != NULL){
            last = last->next;
            n++;
        }
        while(n>0){
            if(p->next->val < x){
                p = p->next;
                n--;
            }else{
                last->next = new ListNode(p->next->val);
                last = last->next;
                p->next = p->next->next;
                n--;
            }
        }
        return head->next;
    }
};
