/*
c++ implementation of BST
*/


#include <iostream>
#include <cstdlib>
using namespace std;

/*
Node declaration
*/

struct treeNode {
	int val;
	treeNode *left;
	treeNode *right;
	treeNode(int x):val(x), left(NULL), right(NULL) {}
};

/*
Class declaration
*/

class BST {
public:
	BST() {root == NULL;};
	//~BST();

	treeNode* find(int x);
	void insert(int x);
	bool remove(int x);
	void inorder();
	void empty();
	treeNode* min();
	treeNode* max();
	//treeNode* clone();

private:
	
	treeNode *root;
	void insert(treeNode* &node, int  x);
	void inorder(treeNode* node);
	treeNode* find(treeNode* node, int x);
	bool remove(treeNode *&z, int x);
	void empty(treeNode* &node);
	treeNode* min(treeNode* node);
	treeNode* max(treeNode* node);
	//treeNode* clone(treeNode* node);
};


void BST::insert(treeNode* &node, int x) {
	if (node == NULL) {
		node = new treeNode(x);
		//node->val = x;
		cout << "inserted " << x << " " << endl;
		return ;
	} 
	if (node->val > x) {
		insert(node->left, x);
		return ;
	} 
	if (node->val < x) {
		insert(node->right, x);
		return ;
	}
}

void BST::insert(int x) {
	insert(root, x);
}

void BST::inorder(treeNode* node) {
	if (node == NULL) return;
	inorder(node->left);
	cout << node->val << " ";
	inorder(node->right);
}

void BST::inorder() {
	cout << "inorder traversal" << endl;
	inorder(root);
}

treeNode* BST::find(treeNode* node, int x) {
	if (node == NULL) return NULL;
	if (x < node->val) return find(node->left, x);
	else if (x > node->val) return find(node->right, x);
	else return node;
}

treeNode* BST::find(int x) {
	return find(root, x);
}

bool BST::remove(int x) {
	return remove(root, x);
}

bool BST::remove(treeNode *&z, int x) {
	if (root == NULL) {
		return false;
	} else {
		if (z->val < x) {
			remove(z->right, x);
		} else if (z->val > x) {
			remove(z->left, x);
		} else if (z->left != NULL && z->right != NULL) {
			z->val = min(z->right)->val;
			remove(z->right, z->val);
		}
		else {
			treeNode *tmp = z;
			z = (z->left != NULL) ? z->left : z->right;
			delete tmp;
			return true;
		} 
	}
}

treeNode* BST::min(treeNode* node) {
	if (node == NULL) return NULL;
	while(node->left) {
		node = node->left;
	}
	return node;
}

treeNode* BST::max(treeNode* node) {
	if (node == NULL) return NULL;
	while(node->right) {
		node = node->right;
	}
	return node;
}

treeNode* BST::min() {
	return min(root);
}

treeNode* BST::max() {
	return max(root);
}

void BST::empty(treeNode* &node) {
	if (node != NULL) {
		empty(node->left);
		empty(node->right);
		delete node;
	}
	node = NULL;
}

void BST::empty() {
	empty(root);
}

/*
treeNode* BST::clone(){
	cout << "start deep clone" << endl;
	return clone(root);
}

treeNode* BST::clone(treeNode* node) {
	if (node == NULL) return NULL;

	treeNode *cnode = new treeNode(node->val);
	cnode->left = clone(node->left);
	cnode->right = clone(node->right);
	return cnode;
}
*/

int main(void)  
{  
/* 
    4 
 2    6 
1 3  5 7 
*/  
    int a[] = {4,2,6,1,3,5,7};  
  
 	BST bst;

    for (int i = 0; i < 7; i++) {
    	bst.insert(a[i]);
    }
    //BuildBST(root,a,sizeof(a) / sizeof(a[0]));  
  
    bst.inorder();  
    cout << "\n";  
  
  	//treeNode *dup = bst.clone(); 
  	cout << endl;
  	//dup.inorder();

    cout << bst.min()->val << "\n";  
    cout << bst.max()->val << "\n";  
  
    bst.remove(6);  
    bst.inorder();
    cout << endl;
  	bst.insert(11);
  	bst.insert(22);
  	bst.remove(3);
  	bst.inorder();
    //BSTNode *dup = Clone(root);  
    //LevelorderTraversal(dup);  
    bst.empty();  
    cout << endl;
    bst.inorder();
    //MakeEmpty(dup);  
    return 0;  
}  











