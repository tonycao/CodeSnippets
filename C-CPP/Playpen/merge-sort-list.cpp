
#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x):val(x), next(nullptr) {}
};

class Solution {
public:
	ListNode* sortList(ListNode* head) {
		if (head == nullptr || head->next == nullptr) {
			return head;
		}

		ListNode* middle = findMiddle(head);
		ListNode* rHead = middle->next;
		middle->next = nullptr;
		
		ListNode* lHead = sortList(head);
		rHead = sortList(rHead);

		ListNode* newHead = merge(lHead, rHead);
		return newHead;
	}

private:
	ListNode* findMiddle(ListNode* head) {
		ListNode* slow = head;
		ListNode* fast = head;

		while (fast != nullptr && fast->next != nullptr && fast->next->next != nullptr) {
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}

	ListNode* merge(ListNode* lHead, ListNode* rHead) {
		ListNode* dummyNode = new ListNode(0);
		ListNode* p = dummyNode;

		while (lHead != nullptr && rHead != nullptr) {
			if (lHead->val < rHead->val) {
				p->next = lHead;
				lHead = lHead->next;
				p = p->next;
			} else {
				p->next = rHead;
				rHead = rHead->next;
				p = p->next;
			}
		}

		if (lHead != nullptr) {
			p->next = lHead;
		}

		if (rHead != nullptr) {
			p->next = rHead;
		}

		p = dummyNode->next;
		delete dummyNode;
		return p;
	}

};

int main() {
	Solution sol;
	ListNode* head = new ListNode(1);
	head->next = new ListNode(3);
	head->next->next = new ListNode(-1);
	head->next->next->next = new ListNode(10);
	head->next->next->next->next = new ListNode(7);
	head->next->next->next->next->next = new ListNode(9);

	head = sol.sortList(head);

	while (head != nullptr) {
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;

}