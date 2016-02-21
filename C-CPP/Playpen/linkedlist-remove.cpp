#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

void remove1(ListNode **head, int to_remove) {
	if (*head == nullptr) return;
	ListNode *cur = *head;
	ListNode *prev = nullptr;

	while(cur) {
		if (cur->val == to_remove) {      // this is the one to remove
			if (prev) {
				ListNode *tmp = cur;
				prev->next = cur->next;   // remove the entry
				delete tmp;
			} else {
				*head = cur->next;         // special case - remove first entry
			}
		} else {
			prev = cur;
		}
		cur = cur->next;
	}
}

void remove2(ListNode **head, int to_remove) {
	ListNode **p = head;   // pointer to a pointer
	ListNode *cur = *head;

	while(cur) {
		if (cur->val == to_remove) {
			ListNode *tmp = cur;
			*p = cur->next;
			delete tmp;
		} else {
			p = &cur->next;
		}
		cur = cur->next;
	}
}

void remove3(ListNode **cur, int to_remove) {
	//ListNode **cur = head;   // pointer to a pointer

	while(*cur) {
		if ((*cur)->val == to_remove) {
			ListNode *tmp = *cur;
			*cur = (*cur)->next;
			delete tmp;
		} else cur = &(*cur)->next;
	}
}

void push(ListNode **head, int new_data) {
	ListNode *newNode = new ListNode(new_data);

	newNode->next = (*head);
	(*head) = newNode;
}

int main() {
	ListNode *head = new ListNode(1);
	push(&head, 2);
	push(&head, 2);
	push(&head, 3);
	push(&head, 2);
	push(&head, 3);


	//remove1(head, 3);
	//remove2(head, 3);
	remove3(&head, 3);
	while(head) {
		cout << head->val << endl;
		head = head->next;
	}

}