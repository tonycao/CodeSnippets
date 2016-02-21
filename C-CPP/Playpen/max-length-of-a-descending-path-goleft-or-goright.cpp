#include <iostream>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left; 
	TreeNode *right;
	TreeNode(int _val): val(_val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
	int maxLength(TreeNode* root) {
		int maxlength = 0;
		maxLength(root, 0, 0, maxlength);
		return maxlength;
	}

private:
	void maxLength(TreeNode* root, int leftlength, int rightlength, int &maxlength) {
		if (root == nullptr) {
		//	cout << leftlength << " " << rightlength << endl;
		//	maxlength = max(maxlength, max(leftlength, rightlength)); 
			return ;
		}
		if (root->left) 
			maxLength(root->left, ++leftlength, 0, maxlength);
		if (root->right) 
			maxLength(root->right, 0, ++rightlength, maxlength);
		maxlength = max(maxlength, max(leftlength, rightlength));
	}
};

int main() {
	TreeNode* root = new TreeNode(0);
	TreeNode* left = new TreeNode(1);
	TreeNode* right = new TreeNode(1);
	TreeNode* lleft = new TreeNode(2);
	TreeNode* rright = new TreeNode(2);
	TreeNode* llleft = new TreeNode(3);
	TreeNode* rrright = new TreeNode(3);
	TreeNode* lllleft = new TreeNode(4);
	TreeNode* rrrright = new TreeNode(4);
	
	root->left = left;
	root->right = right;

	root->left->left = lleft;
	root->right->left = rright;

	//root->left->left->left = rrrright;

	root->left->right = llleft;
	root->left->right->right = rrright;

	root->left->right->right->left = lllleft;

	root->left->right->right->right = rrrright;

	Solution sol;
	cout << sol.maxLength(root) << endl;
	return 0;
}