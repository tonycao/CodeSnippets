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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // write your code here
        /*
        if (lists.size() == 0) {
            return nullptr;
        }
        // method 1: merge two 
        // time: O(KNlogK) % k is the number of lists
        // space: O(1) / O(logk) for recursion
        // https://leetcode.com/discuss/20774/sharing-straightforward-solution-without-structure-vector
        return mergeHelper(lists, 0, lists.size() - 1);
        */
        
        // method 2: priority queue
        // https://leetcode.com/discuss/52745/difference-between-priority-queue-and-heap-implementation
        priority_queue<ListNode*, vector<ListNode *>, compare> q; // min heap
        for (auto l : lists) {
            if (l) q.push(l);
        }
        if (q.empty()) return nullptr;
        
        ListNode* result = q.top();
        q.pop();
        if (result->next) {
            q.push(result->next);
        }
        ListNode* tail = result;
        while(!q.empty()) {
            tail->next = q.top();
            q.pop();
            tail = tail->next;
            if (tail->next) q.push(tail->next);
        }
        return result;
    }
    
private:
    struct compare {
        bool operator() (const ListNode* l, const ListNode* r) {
            return l->val > r->val;
        }
    };

    ListNode* mergeHelper(vector<ListNode *> &lists, int start, int end) {
        if (start == end) {
            return lists[start];
        }
        
        int mid = start + (end - start) / 2;
        ListNode* left = mergeHelper(lists, start, mid);
        ListNode* right = mergeHelper(lists, mid + 1, end);
        return mergeTwoLists(left, right);
    }
    
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;
        
        ListNode* dummy = new ListNode(-1);
        ListNode* cur = dummy;
        
        while(l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                cur->next = l1;
                l1 = l1->next;
            } else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur= cur->next;
        }
        
        if (l1 != nullptr) cur->next = l1;
        if (l2 != nullptr) cur->next = l2;
        
        ListNode* head = dummy->next;
        delete dummy;
        return head;
    }
    
};