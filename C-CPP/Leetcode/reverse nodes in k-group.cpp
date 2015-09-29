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
    ListNode *reverseKGroup(ListNode *head, int k) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (head == NULL && k == 1) return head;
        ListNode* retList = new ListNode(0);
        retList->next = head;
        ListNode* pre = retList;
        int i = 0;
        while( head != NULL){
            i++;
            if(i % k == 0){
                pre = reverse(pre, head->next);
                head = pre->next;
            }else{
                head = head->next;
            }
        }
        return retList->next;
    }

    ListNode *reverse(ListNode *pre, ListNode *next){
        ListNode *last = pre->next;
        ListNode *cur = last->next;
        while(cur != next){
            last->next = cur->next;
            cur->next = pre->next;
            pre->next = cur;
            cur = last->next;
        }
        return last;
    }
};
