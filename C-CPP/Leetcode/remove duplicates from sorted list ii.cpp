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
    ListNode *deleteDuplicates(ListNode *head) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(head == NULL) return NULL;
        if(head->next == NULL) return head;
        ListNode *pre = new ListNode(0);
        pre->next = head;
        head = pre;
        ListNode *list = head;
        while(list->next != NULL){
            ListNode *p = list->next;
            while((p->next!=NULL)&&(p->val == p->next->val)){
                p = p->next;
            }
            if(p != list->next){
                list->next = p->next;
            }else{
                list = list->next;
            }
        }
        return head->next;
    }
};
