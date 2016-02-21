// C++ program for printing vertical order of a given binary tree
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;
 
// Structure for a binary tree node
struct Node
{
    int key;
    Node *left, *right;
};
 
// A utility function to create a new node
struct Node* newNode(int key)
{
    struct Node* node = new Node;
    node->key = key;
    node->left = node->right = NULL;
    return node;
}
 
// Utility function to store vertical order in map 'm'
// 'hd' is horigontal distance of current node from root.
// 'hd' is initally passed as 0
// pre-order traversal
void getVerticalOrder(Node* root, int hd, map<int, vector<int>> &m)
{
    // Base case
    if (root == NULL)
        return;
    
    // iterative
    /*
    queue<pair<int, Node*>> current, next;
    current.push(make_pair(hd,root));
    while(!current.empty()) {
        while(!current.empty()) {
            pair<int, Node*> pnode = current.front();
            current.pop();
            m[pnode.first].push_back(pnode.second->key);
            if (pnode.second->left != nullptr) next.push(make_pair(pnode.first - 1, pnode.second->left));
            if (pnode.second->right != nullptr) next.push(make_pair(pnode.first + 1, pnode.second->right));
        }
        swap(next, current);
    }
    */
 
    // recursive
    // Store current node in map 'm'
    m[hd].push_back(root->key);
 
    // Store nodes in left subtree
    getVerticalOrder(root->left, hd-1, m);
 
    // Store nodes in right subtree
    getVerticalOrder(root->right, hd+1, m);
}
 
// The main function to print vertical oder of a binary tree
// with given root
void printVerticalOrder(Node* root)
{
    // Create a map and store vertical oder in map using
    // function getVerticalOrder()
    map < int,vector<int> > m;
    int hd = 0;
    getVerticalOrder(root, hd, m);
 
    // Traverse the map and print nodes at every horigontal
    // distance (hd)
    //map< int,vector<int> > :: iterator it;
    for (auto it = m.begin(); it != m.end(); it++)
    {
        for (int i = 0; i < it->second.size(); ++i)
            cout << it->second[i] << " ";
        cout << endl;
    }
}

/*
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        vector<vector<int>> ret;
        if(!root) return ret;
        ret.resize(1);
        int l = 0, r = 0;
 
        queue<pair<TreeNode*, int>> que;//node, col
        que.push(pair<TreeNode*, int>(root, 0));
        while(!que.empty()){
            TreeNode *node = que.front().first;
            int col = que.front().second;
            que.pop();
            if(l<=col && col<=r){
                int i = col-l;
                ret[i].push_back(node->val);
            }else if(col<l){
                l--;
                ret.insert(ret.begin(), vector<int>());
                ret.front().push_back(node->val);
            }else{
                r++;
                ret.insert(ret.end(), vector<int>());
                ret.back().push_back(node->val);
            }
            if(node->left) que.push(pair<TreeNode*, int>(node->left, col-1));
            if(node->right) que.push(pair<TreeNode*, int>(node->right, col+1));
        }
        return ret;
    }
};
*/

 
// Driver program to test above functions
int main()
{
    Node *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    root->left->right->right = newNode(10);
    root->right->left->right = newNode(8);
    root->right->right->right = newNode(9);
    root->left->right->right->right = newNode(11);
    cout << "Vertical order traversal is \n";
    printVerticalOrder(root);
    int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    string word("helloworld");
    cout << word.substr(1, 0) << endl;
    cout << word.substr(1, 1) << endl;
    return 0;
}
