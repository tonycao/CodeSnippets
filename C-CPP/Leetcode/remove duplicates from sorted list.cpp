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

        if (head == NULL) return NULL;
        if (head->next == NULL) return head;
        ListNode *list = head;
        while (list->next!=NULL){
            if (list->val == list->next->val){
                list->next = list->next->next;
            }else{
                list = list->next;
            }
        }
        return head;
    }
};
