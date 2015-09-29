/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode* copy_node(UndirectedGraphNode *pNode, unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> &mp){
        if(pNode == NULL) return pNode;
        if(mp.find(pNode) != mp.end()) return mp[pNode];

        UndirectedGraphNode *pRet = new UndirectedGraphNode(pNode->label);
        mp[pNode] = pRet;

        for (int i=0; i < pNode->neighbors.size(); i++)
        {
            //UndirectedGraphNode *pTmp = NULL;
            //if(mp.find(*it) != mp.end()) pRet->neighbors.push_back(mp[*it]);
            //else pRet->neighbors.push_back(copy_node(*it, mp));
            pRet->neighbors.push_back(copy_node(pNode->neighbors[i], mp));
        }

        return pRet;


    }
    //DFS
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(node == NULL) return NULL;

        unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> mp;
        return copy_node(node, mp);
    }

    //BFS
    UndirectedGraphNode *cloneGraph2(UndirectedGraphNode *node){
        if(node==NULL) return NULL;
        queue<UndirectedGraphNode*> queue;
        unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> hashmap;
        UndirectedGraphNode *head=new UndirectedGraphNode(node->label);
        queue.push(node);
        hashmap[node]=head;
        while(!queue.empty())
        {
            UndirectedGraphNode *cur=queue.front();
            queue.pop();
            for(int i=0; i<cur->neighbors.size(); i++)
            {
                UndirectedGraphNode *neighbor=cur->neighbors[i];
                if(hashmap.find(neighbor) == hashmap.end())
                {
                    UndirectedGraphNode *p=new UndirectedGraphNode(neighbor->label);
                    hashmap[cur]->neighbors.push_back(p);
                    hashmap[neighbor]=p;
                    queue.push(neighbor);
                }
                else
                {
                    hashmap[cur]->neighbors.push_back(hashmap[neighbor]);
                }

            }
        }
        return head;
    }
};
