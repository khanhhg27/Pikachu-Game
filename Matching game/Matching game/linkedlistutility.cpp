#include "linkedlistutility.h"

Node* createNode(char data, int x, int y) {
	Node* p = new Node;
	p->key = data;
	p->x = x;
	p->y = y;
	p->pNext = NULL;
	return p;
}

void addHead(Node*& pHead, char data, int x, int y) {
	if (pHead == NULL) {
		pHead = createNode(data, x, y);
		return;
	}
	else {
		Node* p = createNode(data, x, y);
		p->pNext = pHead;
		pHead = p;
		return;
	}
}

void addTail(Node*& pHead, char data, int x, int y) {
	if (pHead == NULL) {
		pHead = createNode(data, x, y);
		return;
	}
	else {
		Node* p = pHead;
		while (p->pNext != NULL) {
			p = p->pNext;
		}
		p->pNext = createNode(data, x, y);
		return;
	}
}

void removeHead(Node*& pHead) {
	if (pHead == NULL)
		return;
	Node* p = pHead;
	pHead = pHead->pNext;
	delete p;
}

void removeTail(Node*& pHead) {
	if (pHead == NULL)
		return;
	if (pHead->pNext == NULL) {
		delete pHead;
		pHead = NULL;
		return;
	}

	Node* p = pHead;
	while (p->pNext->pNext != NULL) {
		p = p->pNext;
	}
	Node* p_ = p->pNext;
	delete p_;
	p->pNext = NULL;
}

void addPos(Node*& pHead, char data, int pos, int x, int y) {
	Node* p = pHead;
	int count = 1;
	while (p != NULL && count < pos - 1) {
		p = p->pNext;
		count++;
	}
	if (p == NULL) {
		return;
	}

	Node* p2 = p->pNext;
	Node* p1 = createNode(data, x, y);
	p->pNext = p1;
	p1->pNext = p2;

}

void removePos(Node*& pHead, int pos) {
	Node* p = pHead;
	int count = 1;
	while (p != NULL && count < pos - 1) {
		p = p->pNext;
		count++;
	}

	if (p == NULL)
		return;

	if (pos == 1) {
		removeHead(pHead);
		return;
	}
	Node* p1 = p->pNext;
	Node* p2 = p1->pNext;

	p->pNext = p2;
	delete p1;
}

void printList(Node* pHead) {
	Node* p = pHead;
	while (p != NULL) {
		cout << p->key << "   ";
		p = p->pNext;
	}
	cout << endl;
	p = pHead;
	while (p != NULL) {
		cout << p->x << "   ";
		p = p->pNext;
	}
	cout << endl;
	p = pHead;
	while (p != NULL) {
		cout << p->y << "   ";
		p = p->pNext;
	}

	cout << endl;
}

void deleteLinkedList(Node* pHead) {
	while (pHead->pNext != NULL) {
		Node* x = pHead;
		pHead = pHead->pNext;
		delete x;
	}
	delete pHead;
}

Node* getNode(Node* pHead, int pos) {
	Node* p = pHead;
	for (int i = 0; i < pos; i++) {
		p = p->pNext;
	}

	return p;
}