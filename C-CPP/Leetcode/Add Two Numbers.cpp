// Add Two Numbers

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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode *inputl1 = l1, *inputl2 = l2;
        ListNode *result = NULL, *tail = NULL;


        int carry = 0;
        while(inputl1 != NULL || inputl2 != NULL || carry != 0){
            int num1 = inputl1 == NULL ? 0 : inputl1->val;
            int num2 = inputl2 == NULL ? 0 : inputl2->val;
            int sum = num1 + num2 + carry;
            carry = sum / 10;
            sum %= 10;

            if (result == NULL) {
                result = new ListNode(sum);
                tail = result;
            } else{
                tail->next = new ListNode(sum);
                tail = tail->next;
            }

            inputl1 = inputl1 == NULL ? NULL : inputl1->next;
            inputl2 = inputl2 == NULL ? NULL : inputl2->next;

        }
        return result;
    }
};
