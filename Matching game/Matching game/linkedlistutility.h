#pragma once

#include "console.h"
#include "board.h"

using namespace std;

struct Node {
	char key;
	int x;
	int y;
	Node* pNext;
};

Node* createNode(char data, int, int);
void addHead(Node*& pHead, char data);
void addTail(Node*& pHead, char data, int, int);
void removeHead(Node*& pHead);
void removeTail(Node*& pHead);
void addPos(Node*& pHead, char data, int pos, int, int);
void removePos(Node*& pHead, int pos);
void printList(Node* pHead);
void deleteLinkedList(Node* pHead);
Node* getNode(Node* pHead, int pos);