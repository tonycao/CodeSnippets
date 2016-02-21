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
    bool isPalindrome(ListNode* head) {
        // method 1: O(1) space
        /*
        if (head == nullptr) return true;
        auto front = head, slow = head, fast = front;//->next;
        
        // find the middle node
        while(fast && fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // reverse second half
        ListNode* prev = nullptr;
        ListNode* middle = slow->next;
        while(middle) {
            auto tmp = middle->next;
            middle->next = prev;
            prev = middle;
            middle = tmp;
        }
        
        // compare
        middle = prev;
        while(front && middle) {
            if (front->val != middle->val) return false;
            front = front->next, middle = middle->next;
        }
        return true;
        */
        
        // method 2: not O(1) space
        tmp = head;
        return check(head);
    }
private:
    bool check(ListNode *p) {
        if (NULL == p) return true;
        bool isPal = check(p->next) & (tmp->val == p->val);
        tmp = tmp->next;
        return isPal;
    }
    ListNode *tmp;

};