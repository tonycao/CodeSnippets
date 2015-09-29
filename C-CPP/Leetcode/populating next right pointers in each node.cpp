/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        queue<TreeLinkNode *> q;
        if(root){
            q.push(root);
            q.push(NULL);
        }
        while(q.size()){
            TreeLinkNode *cur = q.front();
            q.pop();
            if(cur){
                cur->next = q.font();
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }else{
                if(q.size()) q.push(NULL);
            }
        }
    }
};

// algorithm2

void connect(Node* p) {
  if (p == NULL)
    return;
  if (p->leftChild == NULL || p->rightChild == NULL)
    return;
  Node* rightSibling;
  Node* p1 = p;
  while (p1) {
    if (p1->nextRight)
      rightSibling = p1->nextRight->leftChild;
    else
      rightSibling = NULL;
    p1->leftChild->nextRight = p1->rightChild;
    p1->rightChild->nextRight = rightSibling;
    p1 = p1->nextRight;
  }
  connect(p->leftChild);
}
