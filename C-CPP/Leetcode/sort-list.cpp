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
    /* //recursive implementation
    
    ListNode* sortList(ListNode* head) {
        if (head == NULL || head->next == NULL)
            return head;
        ListNode *p = head, *q = head; // fast and slow Nodes
        while( p->next != NULL && p->next->next != NULL) {
            p = p->next->next;
            q = q->next;
        }
        
        p = q;
        q = q->next;
        p->next = NULL;
        p = sortList(head);
        q = sortList(q);
        return merge(p, q);
    }
    
    ListNode *merge(ListNode*p, ListNode*q) {
        ListNode *h = new ListNode(0), *c = h;
        while(p != NULL && q != NULL) {
            if(p->val < q->val) {
                c->next = p;
                p = p->next;
                c = c->next;
            } else {
                c->next = q;
                q = q->next;
                c = c->next;
            }
        }
        if (p != NULL) c->next = p;
        if (q != NULL) c->next = q;
        c = h->next; // do not foget, let c = head;
        delete h;
        return c;
    }
    */
    // iterative implementation
    ListNode *sortList(ListNode *head) {
        if (head == NULL || head->next == NULL) 
            return head;
        int len = 0, l = 1;
        ListNode *h = new ListNode(0), *p = head, *q, *pre;
        h->next = head;
        while(p != NULL) {
            p = p->next;
            len++;
        }
        
        while(l < len) {
            pre = h;
            p = h->next;
            q = move(p, l);
            while(q != NULL) {
                pre->next = merge(p, q, l);
                pre = move(pre, 2*l);
                p = move(pre, 1);
                q = move(p, l);
            }
            l += l;
        }
        
        p = h->next;
        delete(h);
        return p;
    }
    
    ListNode *move(ListNode*p, int l) {
        while(p != NULL && l-- > 0) {
            p = p->next;
        }
        return p;
    }
    
    ListNode* merge(ListNode *h1, ListNode* h2, int l) {
        ListNode *h = new ListNode(0), *p = h, *beh = move(h2, l);
        int l1 = 0, l2 = 0;
        while( (h1 != NULL && l1 < l) || (h2 != NULL && l2 < l)) {
            if ((h1 != NULL && l1 < l && h2 != NULL && l2 < l && h1->val < h2->val) || 
                (h2 == NULL) || (l2 == l)) {
                p->next = h1;
                p = p->next;
                h1 = h1->next;
                l1++;
            }else {
                p->next = h2;
                p = p->next;
                h2 = h2->next;
                l2++;
            }
        }
        
        p->next = beh;
        p = h->next;
        delete(h);
        return p;
    }
};