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
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        ListNode* h = head;
        for(int i=0; i<n-m; i++){
            int k1 = m+i;
            int k2 = n-i;
            if(k1>=k2) return head;
            ListNode* p = h;
            ListNode* q = h;
            while(k1-1>0){
                p = p->next;
                k1--;
            }
            while(k2-1>0){
                q = q->next;
                k2--;
            }
            int tmp = p->val;
            p->val = q->val;
            q->val = tmp;
        }
        return head;
    }
};
