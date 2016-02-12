
// bottom up
Node *LCA(Node *root, Node *p, Node *q) {
  if (!root) return NULL;
  if (root == p || root == q) return root;
  Node *L = LCA(root->left, p, q);
  Node *R = LCA(root->right, p, q);
  if (L && R) return root;  // if p and q are on both sides
  return L ? L : R;  // either one of p,q is on one side OR p,q is not in L&R subtrees
}

// top down
// Return #nodes that matches P or Q in the subtree.
int countMatchesPQ(Node *root, Node *p, Node *q) {
  if (!root) return 0;
  int matches = countMatchesPQ(root->left, p, q) + countMatchesPQ(root->right, p, q);
  if (root == p || root == q)
    return 1 + matches;
  else
    return matches;
}

Node *LCA(Node *root, Node *p, Node *q) {
  if (!root || !p || !q) return NULL;
  if (root == p || root == q) return root;
  int totalMatches = countMatchesPQ(root->left, p, q);
  if (totalMatches == 1)
    return root;
  else if (totalMatches == 2)
    return LCA(root->left, p, q);
  else /* totalMatches == 0 */
    return LCA(root->right, p, q);
}
