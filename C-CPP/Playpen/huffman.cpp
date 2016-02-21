#include<queue>
#include<cstring>
#include<iostream>

//#define MAX_TREE_HEIGHT 50
using namespace std;


class Huffman {
public:
	class Node{
	public:
		int freq;
		char ch;
		class Node *left, *right;
		Node(char c, int f):freq(f), ch(c) {
			left = right = nullptr;
		}
	};

	// compare functor for min heap
	class cmp{
	public:
		bool operator()(Node *a, Node *b) {
			return a->freq > b->freq;
		}
	};

	Huffman() {
		//pq.clear();
	}

	~Huffman() {
		deleteTree(root);
	}

	Node* newNode(char ch,int freq) {
		Node *temp = new Node(ch, freq);
		//temp->freq = freq;
		//temp->ch = ch;
		//temp->left = temp->right=NULL;
		return temp;
	}

	void printCodes(Node *root, string code) {
		if (!root) return;

		if (root->ch != '$') {
			cout << root->ch << ": " << code << endl;
		}

		printCodes(root->left, code + "0");
		printCodes(root->right, code + "1");

	}

	void HuffmanCodes(char arr[],int freq[],int size){

		//int code[MAX_TREE_HEIGHT];
		Node *left, *right;
		  // min heap here

		for(int i=0;i<size;i++){
			pq.push(newNode(arr[i],freq[i]));
		}

		while(pq.size() > 1) {
			// remove left
			left = pq.top();
			pq.pop();

			// remove right
			right = pq.top();
			pq.pop();

			Node *temp = newNode('$', left->freq + right->freq);
			temp->left = left;
			temp->right = right;
			pq.push(temp);
		}
		root = pq.top();
		pq.pop();

		printCodes(root, "");
	}

	void deleteTree(Node* root) {
		if (root != nullptr) {

			deleteTree(root->left);
			deleteTree(root->right);

			delete(root);

			if (root->left) root->left = nullptr;
			if (root->right) root->right = nullptr;

			root = nullptr;
		}
	}

private:
	priority_queue<Node*, vector<Node*>, cmp> pq;
	Node* root;
	//const int MAX_TREE_HEIGHT = 50;
};
int main()
{
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'k'};
    int freq[] = {5, 9, 12, 13, 16, 45, 21};
    int size = sizeof(arr)/sizeof(arr[0]);
    Huffman huff;
    huff.HuffmanCodes(arr, freq, size);
    return 0;
}