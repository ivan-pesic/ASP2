#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <iomanip>

using namespace std;

struct Action {
	char name[256];
	int priority;

	friend ostream& operator <<(ostream& os, const Action& action) {
		return os << "(" << action.name << " : " << action.priority << ")" << endl;
	}
	friend bool operator<(const Action& a1, const Action& a2) {
		return a1.priority < a2.priority || a1.priority == a2.priority && strcmp(a1.name, a2.name) < 0;
	}
	friend bool operator >(const Action& a1, const Action& a2) {
		return a1.priority > a2.priority || a1.priority == a2.priority && strcmp(a1.name, a2.name) > 0;
	}
	friend bool operator ==(const Action& a1, const Action& a2) {
		return a1.priority == a2.priority && !strcmp(a1.name, a2.name);
	}
	friend bool operator !=(const Action& a1, const Action& a2) {
		return a1.priority != a2.priority || strcmp(a1.name, a2.name);
	}
	friend bool operator <=(const Action& a1, const Action& a2) {
		return a1 < a2 || a1 == a2;
	}
	friend bool operator >=(const Action& a1, const Action& a2) {
		return a1 > a2 || a1 == a2;
	}
};

struct Node {
	int cnt;
	Action* action[3];
	Node* left;
	Node* middle1;
	Node* middle2;
	Node* right;
	Node* parent;
	Node() {
		for (int i = 0; i < 3; i++)
			action[i] = nullptr;
		left = middle1 = middle2 = right = parent = nullptr;
		cnt = 0;
	}
	~Node() {
		for (int i = 0; i < 3; i++) {
			if(action[i])
				delete action[i];
		}
		left = middle1 = middle2 = right = parent = nullptr;
	}
};

class Tree234 {
	private:
		Node* root;
		int height;
	public:
		Tree234();
		Tree234(const Tree234&) = delete;
		Tree234(Tree234&&) = delete;
		~Tree234();

		Action* searchByPriority(int);
		void insertAction(Action* action);

		void deleteByPriority(int priority);
		void deleteMaxPriority();

		void deleteFromTree(Node*, int);
		void printRB();

		void changePriority(string name, int priority);

		int findNumberOfActions(int);
		friend ostream& operator <<(ostream&, const Tree234&);
};

int menu();
bool readAction(Action*&, istream&);
void insertFromFile(ifstream&, Tree234&);
bool lexico(Action*, Action*);
bool prio(Action*, Action*);
void insertInZero(Action*&, Node*&, Node*, Node*);
void insertInOne(Action*&, Node*&, Node*, Node*);
void insertInTwo(Action*&, Node*&, Node*, Node*);
void rearrange(Node*&, Node*&, Action*&, Node*, Node*);
void setPointers(Node*&, Action*&, Node*&, Node*&);
bool inNode(Node*&, Action*&);