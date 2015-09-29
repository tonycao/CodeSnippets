/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if (head == NULL) return NULL;
        RandomListNode *result = NULL;
        RandomListNode *pold = head, *pnew = result, *poldNext = NULL;

        while(pold){
            poldNext = pold->next;
            pnew = new RandomListNode(pold->label);
            pold->next = pnew;
            pnew->next = poldNext;

            if(result == NULL) result = pnew;
            pold = poldNext;
        }

        pold = head;
        while(pold){
            if(pold->random) pold->next->random = pold->random->next;
            pold = pold->next->next;
        }

        pold = head;
        pnew = result;
        while(pnew->next){
            pold->next = pnew->next;
            pold = pold->next;
            pnew->next = pold->next;
            pnew = pnew->next;
        }

        pold->next = NULL;
        pnew->next = NULL;
        return result;
    }
};


//algorithm 2 use hashtable
    RandomListNode *copyRandomList(RandomListNode *head) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(head==NULL) return NULL;
        unordered_map<RandomListNode*, RandomListNode*> node_map;
        RandomListNode *n=head, *copyn=new RandomListNode(head->label), *nextn, *randn;
        node_map[n]=copyn;
        while(n)
        {
            randn = n->random;
            if(randn!=NULL)
            {
                if(node_map.count(randn)==0)
                {
                    RandomListNode *tmp = new RandomListNode(randn->label);
                    node_map[randn] = tmp;
                    node_map[n]->random = tmp;
                }
                else
                {
                    node_map[n]->random = node_map[randn];
                }
            }
            nextn = n->next;
            if(nextn!=NULL)
            {
                if(node_map.count(nextn)==0)
                {
                    RandomListNode *tmp = new RandomListNode(nextn->label);
                    node_map[nextn] = tmp;
                    node_map[n]->next = tmp;

                }
                else
                {
                    node_map[n]->next = node_map[nextn];
                }
            }
            n = n->next;
        }
        return copyn;
    }
