#include "avl.hpp"

void rightRotation(treeNode*& x) {
	treeNode* y = x->left;
	treeNode* temp = y->right;
	y->right = x;
	x->left = temp;
}

void leftRotation(treeNode*& x) {
	treeNode* y = x->right;
	treeNode* temp = y->left;
	y->left = x;
	x->right = temp;
}

void insertAVL(treeNode*& root, int k) {
	treeNode* fp = nullptr;
	treeNode* fx = nullptr;
	treeNode* p = root;
	treeNode* x = p;
	treeNode* q;

	while (p != nullptr) {
		//if (k == p->key)
			//return; //return p;
		if (k <= p->key) //!
			q = p->left;
		else
			q = p->right;
		if (q) {
			if (q->b) {
				fx = p;
				x = q;
			}
		}
		fp = p;
		p = q;
	}
	q = formNode(k);
	q->b = 0;
	if (k <= fp->key) //!
		fp->left = q;
	else
		fp->right = q;

	if (k <= x->key) //!
		p = x->left;
	else
		p = x->right;

	treeNode* y = p;
	while (p != q) {
		if (k <= p->key) { //!
			p->b = 1;
			p = p->left;
		}
		else {
			p->b = -1;
			p = p->right;
		}
	}
	char imbal;
	if (k <= x->key) //!
		imbal = 1;
	else
		imbal = -1;

	if (x->b == 0) {
		x->b = imbal;
		return; //return q;
	}
	if (x->b != imbal) {
		x->b = 0;
		return; //return q;
	}
	if (y->b == imbal) {
		p = y;
		if (imbal == 1)
			rightRotation(x);
		else
			leftRotation(x);

		x->b = y->b = 0;
	}
	else {
		if (imbal == 1) {
			p = y->right;
			leftRotation(y);
			x->left = p;
			rightRotation(x);
		}
		else {
			p = y->left;
			x->right = p;
			rightRotation(y);
			leftRotation(x);
		}
		if (p->b == 0)
			x->b = y->b = 0;
		else {
			if (p->b == imbal) {
				x->b = -imbal;
				y->b = 0;
			}
			else {
				x->b = 0;
				y->b = imbal;
			}
			p->b = 0;
		}
	}
	if (!fx)
		root = p;
	else {
		if (x == fx->right)
			fx->right = p;
		else
			fx->left = p;
	}
	return; //return q;
}

treeNode* formNode(int key) {
	treeNode* newNode = new treeNode;

	newNode->left = nullptr;
	newNode->right = nullptr;
	newNode->key = key;
	newNode->b = 0;

	return newNode;
}

treeNode* formTree(int* arr, int n) {
	treeNode* tree = nullptr;
	for (int i = 0; i < n; i++) {
		if(tree)
			insertAVL(tree, arr[i]);
		else
			tree = formNode(arr[i]);
	}

	return tree;
}

void searchKey(treeNode* root, int key) {
	treeNode* p = root;

	while (p != nullptr && key != p->key) {
		if (key < p->key)
			p = p->left;
		else
			p = p->right;
	}
	if (p)
		cout << "Kljuc uspesno pronadjen." << endl;
	else
		cout << "Kljuc ne postoji u stablu." << endl;
}

void deleteTree(treeNode* root) {
	if (!root)
		return;

	struct stackElement {
		treeNode* node;
		bool flag;
	};

	treeNode* next = root;
	stack <stackElement> s;
	
	while (next != nullptr) {
		s.push({ next, true });
		next = next->left;
	}
	while (!s.empty()) {
		stackElement elem = s.top();
		next = elem.node;
		s.pop();
		if (elem.flag) {
			s.push({ next, false });
			next = next->right;
			while (next != nullptr) {
				s.push({ next, true });
				next = next->left;
			}
		}
		else {
			delete next;
		}
	}
}

treeNode* copyTree(treeNode* root) {
	if (!root)
		return nullptr;

	struct stackElement {
		treeNode* node;
		bool flag;
	};

	treeNode* next = root;
	stack <stackElement> s;

	stack <treeNode*> copyStack;

	while (next != nullptr) {
		s.push({ next, true });
		next = next->left;
	}
	while (!s.empty()) {
		stackElement elem = s.top();
		next = elem.node;
		s.pop();
		if (elem.flag) {
			s.push({ next, false });
			next = next->right;
			while (next != nullptr) {
				s.push({ next, true });
				next = next->left;
			}
		}
		else {
			treeNode* newNode = formNode(next->key);
			treeNode* tmp;
			if (next->right) {
				tmp = copyStack.top();
				copyStack.pop();
				newNode->right = tmp;
			}
			if (next->left) {
				tmp = copyStack.top();
				copyStack.pop();
				newNode->left = tmp;
			}
			copyStack.push(newNode);
		}
	}
	treeNode* copiedTree = copyStack.top();
	copyStack.pop();
	return copiedTree;
}	