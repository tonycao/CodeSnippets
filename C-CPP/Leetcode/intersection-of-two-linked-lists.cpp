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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == NULL || headB == NULL) return NULL;
        ListNode *curA = headA;
        ListNode *curB = headB;
        
        /*/ method 1
        // space O(n)
        set<ListNode *> nodeSet;
        while(curA != NULL) {
            nodeSet.insert(curA);
            curA = curA->next;
        }
        while(curB != NULL) {
            if (nodeSet.find(curB) != nodeSet.end()) {
                return curB;
            } else {
                curB = curB->next;
            }
        }
        */
        
        // method 2
        // time: O(n), space O(1)
        int m = 0, n = 0;
        while(curA) {
            curA = curA->next;
            m++;
        }
        while(curB) {
            curB = curB->next;
            n++;
        }
        
        int diff = abs(m - n);
        curA = headA;
        curB = headB;

        while(diff) {
            if (m > n)
                curA = curA->next;
            else curB = curB->next;
            diff--;
        }
    
        
        while(curA != curB) {
            curA = curA->next;
            curB = curB->next;
        }
        
        return curA;
    }
};