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
    ListNode *swapPairs(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (head == NULL || head->next == NULL) return head;
        ListNode *ret = new ListNode(0); //head->next;
        ret->next = head;
        ListNode *nl = ret, *nr = head;
        while( nr != NULL && nr->next != NULL){
            ListNode *tmp = nr->next->next;
            nr->next->next = nl->next;
            nl->next = nr->next;
            nr->next = tmp;
            nl = nr;
            nr = nl->next;
        }
        head = ret->next;
        delete ret;
        return head;
    }
};
