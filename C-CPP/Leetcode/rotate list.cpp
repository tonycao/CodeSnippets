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
    ListNode *rotateRight(ListNode *head, int k) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(head){
            int len = 1;
            ListNode *p = head;
            while(p->next){
                p = p->next;
                len++;
            }
            p->next = head;
            k %= len;
            int step = len - k;
            while(step>0){
                p = p->next;
                step--;
            }
            head = p->next;
            p->next = NULL;
        }
        return head;
    }
};
