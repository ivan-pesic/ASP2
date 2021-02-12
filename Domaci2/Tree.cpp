#include "Tree.h"

Tree234::Tree234() {
	root = nullptr;
	height = 0;
}

Tree234::~Tree234() {
	queue <Node*> q;
	Node* next = root;
	if(next)
		q.push(next);
	while (!q.empty()) {
		next = q.front();
		q.pop();
		if (next->left)
			q.push(next->left);
		if (next->middle1)
			q.push(next->middle1);
		if (next->middle2)
			q.push(next->middle2);
		if (next->right)
			q.push(next->right);
		delete next;
	}
	root = nullptr;
}

bool readAction(Action * &action, istream & in) {
		string line;
		getline(in, line);
		if (!line.length()) {
			action = nullptr;
			return false;
		}
		action = new Action;
		int lastWhitespace = line.find_last_of(" ");
		strcpy_s(action->name, (line.substr(0, lastWhitespace)).c_str());
		action->priority = stoi(line.substr(lastWhitespace + 1));
		return true;
}

void insertFromFile(ifstream& file, Tree234& tree) {
	Action* action = nullptr;
	while (readAction(action, file)) {
		if (!strcmp(action->name, "r")) {
			//cout << "A" << endl;
		}
		tree.insertAction(action);
		
		//cout << *action << endl;
		//cout << tree;
		//cout << endl << endl << endl;
	}
}

void insertInZero(Action*& action, Node*& q, Node* left, Node* right) {
	q->action[1] = action;
	q->middle1 = left;
	q->middle2 = right;
	q->cnt++;
	if (left && right)
		left->parent = right->parent = q;
}

void insertInOne(Action*& action, Node*& q, Node* left, Node* right) {
	if (*action < *q->action[1]) {
		q->action[0] = action;
		q->left = left;
		q->middle1 = right;
	}
	else if (*action > * q->action[1]) {
		q->action[2] = action;
		q->middle2 = left;
		q->right = right;
	}
	q->cnt++;
	if (left && right)
		left->parent = right->parent = q;
}

void insertInTwo(Action*& action, Node*& q, Node* left, Node* right) {
	
	if (q->action[0] && q->action[1]) {
		if (*action < *q->action[0]) {
			q->action[2] = q->action[1];
			q->action[1] = q->action[0];
			q->action[0] = action;
			q->right = q->middle2; // !!!
			q->middle2 = q->middle1; // !!!
			q->left = left;
			q->middle1 = right;
		}
		else if (*action < *q->action[1]) {
			q->action[2] = q->action[1];
			q->action[1] = action;
			q->right = q->middle2; // !!!
			q->middle2 = right;
			q->middle1 = left;
		}
		else {
			q->action[2] = action;
			q->middle2 = left;
			q->right = right;
		}
	}
	else if (q->action[1] && q->action[2]) {
		if (*action < *q->action[1]) {
			q->action[0] = action;
		}
		else if (*action < *q->action[2]) {
			q->action[0] = q->action[1];
			q->left = q->middle1;
			q->middle1 = left;
			q->middle2 = right;
			q->action[1] = action;
		}
		else {
			q->action[0] = q->action[1];
			q->action[1] = q->action[2];
			q->action[2] = action;
			q->left = q->middle1;
			q->middle1 = q->middle2;
			q->middle2 = q->right;
			q->right = right;
			q->middle2 = left;
		}
	}
	if (left && right)
		left->parent = right->parent = q;
	q->cnt++;
}

void rearrange(Node*& left, Node*& right, Action*& action, Node* actionLeft, Node* actionRight) {
	insertInZero(left->action[2], right, left->middle2, left->right);
	left->action[2] = nullptr; // staro mesto je null
	left->right = nullptr;
	Action* oldAction = left->action[1];
	left->action[1] = left->action[0];
	left->action[0] = nullptr;
	left->middle2 = left->middle1;
	left->middle1 = left->left;
	left->left = nullptr;
	if (*action < *oldAction) {
		insertInOne(action, left, actionLeft, actionRight);
		//if(actionLeft && actionRight)
			//actionLeft->parent = actionRight->parent = left;
		left->cnt = 2;
	}
	else {
		insertInOne(action, right, actionLeft, actionRight);
		//if(actionLeft && actionRight)
			//actionLeft->parent = actionRight->parent = right;
		left->cnt = 1;
	}
}

bool inNode(Node*& node, Action*& action) {
	for (int pos = 0; pos < 3; pos++) {
		if (node->action[pos] && *action == *node->action[pos])
			return true;
	}
	return false;
}

void printNode(Node* node, ostream& out) {
	cout << "[";
	for (int i = 0; i < 3; i++) {
		if (node->action[i] && i & 1) {
			out << "\x1B[1m\033[90m" << setw(3) << node->action[i]->priority << node->action[i]->name[0] << "\x1B[0m";
		}
		else if (node->action[i]) {
			out << "\x1B[1m\033[31m" << setw(3) << node->action[i]->priority << node->action[i]->name[0] << "\x1B[0m";
		}	
		else {
			out << "    ";
		}
		if(i < 2)
			out << "|";
	}
	out << "]";
}

ostream& operator<<(ostream& out, const Tree234& tree) {
	Node* root = tree.root;
	int height = tree.height;
	if (!root)
		return out;
	int lastLvl = 0;
	int maxWidth = pow(4, height) * 18;
	int spacing = maxWidth;
	Node* next = root;
	pair <Node*, int> elem;
	queue <pair<Node*, int>> q;
	q.push({ next, lastLvl });
	while (!q.empty() && lastLvl <= height) {
		auto tmp = q.front();
		q.pop();
		if (lastLvl != tmp.second) {
			lastLvl = tmp.second;
			out << endl << endl;
			if (lastLvl > height) return out;
			spacing = maxWidth / pow(4, lastLvl);
		}
		for (int i = 0; i < (spacing - 18) / 2; i++)
			out << " ";

		if (tmp.first) {
			out << " ";
			printNode(tmp.first, out);
			out << " ";
			q.push({ tmp.first->left , lastLvl + 1 });
			q.push({ tmp.first->middle1 , lastLvl + 1 });
			q.push({ tmp.first->middle2 , lastLvl + 1 });
			q.push({ tmp.first->right, lastLvl + 1 });
		}
		else {
			for (int i = 0; i < 18; i++)
				out << " ";
			q.push({ nullptr, lastLvl + 1 });
			q.push({ nullptr, lastLvl + 1 });
			q.push({ nullptr, lastLvl + 1 });
			q.push({ nullptr, lastLvl + 1 });
		}
		for (int i = 0; i < (spacing - 18) / 2; i++)
			out << " ";
	}
	while (!q.empty()) q.pop();
	return out;
}

pair <Node*, int> getLeft(Node* node, int pos) {
	switch (pos) {
	case 0:
		return {node->left, 1};
		break;
	case 1:
		if (node->action[0]) {
			return { node, 0 };
		}
		else {
			return { node->middle1, 1 };
		}
		break;
	case 2:
		return { node->middle2, 1 };
		break;
		default: cout << "Impossible!" << endl;
	}
}

pair <Node*, int> getRight(Node* node, int pos) {
	switch (pos) {
	case 0:
		return { node->middle1, 1 };
		break;
	case 1:
		if (node->action[2]) {
			return { node, 2 };
		}
		else {
			return { node->middle2, 1 };
		}
		break;
	case 2:
		return { node->right, 1 };
		break;
	default: cout << "Impossible!" << endl;
	}
}

int rbHeight(Node* root) {
	int h = 0;
	Node* next = root;
	if (!next)
		return 0;
	int currLevel = 0, lastLvl = 0;
	queue <pair<Node*, int>> q;
	bool flag = true;	
	queue <int> depth;
	q.push({ next, 1 });
	depth.push(currLevel);

	while (!q.empty()) {
		auto tmp = q.front();
		q.pop();
		next = tmp.first;
		int currDepth = depth.front();
		depth.pop();
		if (lastLvl != currDepth) {
			lastLvl = currDepth;
			h++;
		}
		if (tmp.first) {
			// ubacivanje odgovarajuceg levog i desnog sina
			pair <Node*, int> left = getLeft(next, tmp.second);
			pair <Node*, int> right = getRight(next, tmp.second);
			if (left.first) {
				q.push(left);
				depth.push(currDepth + 1);
			}
			if (right.first) {
				q.push(right);
				depth.push(currDepth + 1);
			}
		}
	}
	return h;
}

Action* Tree234::searchByPriority(int action) {
	Node* tmp = root;
	Node* q = tmp;
	while (tmp) {
		q = tmp;
		if (tmp->action[0] && action <= tmp->action[0]->priority) {
			if (action == tmp->action[0]->priority) {
				return tmp->action[0];
			}
			else {
				tmp = tmp->left;
			}
		}
		else if (tmp->action[1] && action <= tmp->action[1]->priority) {
			if (action == tmp->action[1]->priority) {
				return tmp->action[1];
			}
			else {
				tmp = tmp->middle1;
			}
		}
		else if (tmp->action[2] && action <= tmp->action[2]->priority) {
			if (action == tmp->action[2]->priority) {
				return tmp->action[2];
			}
			else {
				tmp = tmp->middle2;
			}
		}
		else {
			tmp = tmp->right;
		}
	}
	return nullptr;
}

void Tree234::insertAction(Action* action) {
	if (!root) {
		root = new Node;
		root->action[1] = action;
		root->cnt++;
		return;
	}
	
	Node* tmp = root;
	Node* q = tmp;
	
	while (tmp) {
		q = tmp;
		if (inNode(tmp, action)) {
			cout << "Neuspesan unos. Akcija vec postoji!" << endl;
			delete action;
			return;
		}
		if (tmp->action[0] && *action < *tmp->action[0]) {
			tmp = tmp->left;
		}
		else if (!tmp->action[1] || tmp->action[1] && *action < *tmp->action[1]) {
			tmp = tmp->middle1;
		}
		else if (!tmp->action[2] || tmp->action[2] && *action < *tmp->action[2]) {
			tmp = tmp->middle2;
		}
		else {
			tmp = tmp->right;
		}
	}

	if (q->cnt == 1) { //cvor ima samo 1 akciju
		insertInOne(action, q, nullptr, nullptr);
	}
	else if (q->cnt == 2) { //cvor ima 2 akcije
		insertInTwo(action, q, nullptr, nullptr);
	}
	else { //cvor ima 3 akcije, vrsi se prelamanje
		Node* parent = q->parent;
		Action* currAction = q->action[1];
		Node* left = q;
		Node* right = new Node;
		left->parent = right->parent = parent;
		rearrange(left, right, action, nullptr, nullptr);
		while (true) {
			if (!parent) {
				Node* newRoot = new Node;
				root = newRoot;
				insertInZero(currAction, newRoot, left, right);
				//if(left && right)
					//left->parent = right->parent = newRoot;
				height++;
				break;
			}
			else {
				if (parent->cnt == 1) {
					insertInOne(currAction, parent, left, right);
					//cout << *currAction;
					//if (left && right)	
						//left->parent = right->parent = parent;
					break;
				}
				else if (parent->cnt == 2) {
					insertInTwo(currAction, parent, left, right);
				//	if (left && right)
					//	left->parent = right->parent = parent;
					break;
				}
				else {
					Node* newLeft = parent;
					Node* newRight = new Node;
					Action* newAction = parent->action[1];
					parent = parent->parent;
					rearrange(newLeft, newRight, currAction, left, right);
					currAction = newAction;
					left = newLeft;
					right = newRight;
					
				}
			}
		}
	}
}

void Tree234::deleteByPriority(int priority) {
	Node* tmp = root;
	Node* q = tmp;
	while (tmp) {
		q = tmp;
		if (tmp->action[0] && priority <= tmp->action[0]->priority) {
			if (priority == tmp->action[0]->priority) {
				cout << *tmp->action[0] << endl;
				deleteFromTree(tmp, 0);
				
				return;// tmp->action[0];
			}
			else {
				tmp = tmp->left;
			}
		}
		else if (tmp->action[1] && priority <= tmp->action[1]->priority) {
			if (priority == tmp->action[1]->priority) {
				cout << *tmp->action[1] << endl;
				deleteFromTree(tmp, 1);
				
				return;// tmp->action[1];
			}
			else {
				tmp = tmp->middle1;
			}
		}
		else if (tmp->action[2] && priority <= tmp->action[2]->priority) {
			if (priority == tmp->action[2]->priority) {
				cout << *tmp->action[2] << endl;
				deleteFromTree(tmp, 2);
				
				return;// tmp->action[2];
			}
			else {
				tmp = tmp->middle2;
			}
		}
		else {
			tmp = tmp->right;
		}
	}
	cout << "Brisanje neuspesno. Ne postoji akcija sa trazenim prioritetom." << endl;	
}

Node* findBrother(Node* parent, Node* curr) {
	for (int i = 0; i < 3; i++) {
		if (parent->action[i]) {
			pair <Node*, int> left = getLeft(parent, i);
			pair <Node*, int> right = getRight(parent, i);
			if (left.first == curr) {
				if (right.first == parent)
					return nullptr;
				return right.first;
			}
			else if (right.first == curr) {
				if (left.first == parent)
					return nullptr;
				return left.first;
			}
		}
	}
	return nullptr;
}

int findIndexOfParent(Node* parent, Node* q) {

if (parent->action[0] && (parent->left == q || parent->middle1 == q))
		return 0;
	else if (parent->action[1] && (parent->middle1 == q || parent->middle2 == q))
		return 1;
	else
		return 2;
}

Action* getMinAction(Node* brother) {
	Action* a;
	if (brother->action[0]) {
		a = brother->action[0];
		brother->action[0] = nullptr;
		brother->cnt--;
		brother->left = nullptr;
		return a;
	}
	else if (brother->action[1]) {
		a = brother->action[1];
		brother->action[1] = brother->action[2];
		brother->action[2] = nullptr;
		brother->cnt--;
		brother->middle1 = brother->middle2;
		brother->middle2 = brother->right;
		brother->right = nullptr;
		return a;
	}
}
Action* getMaxAction(Node* brother) {
	Action* a;
	if (brother->action[2]) {
		a = brother->action[2];
		brother->action[2] = nullptr;
		brother->cnt--;
		brother->right = nullptr;
		return a;
	}
	else if (brother->action[1]) {
		a = brother->action[1];
		brother->action[1] = brother->action[0];
		brother->action[0] = nullptr;
		brother->cnt--;
		brother->middle2 = brother->middle1;
		brother->middle1 = brother->left;
		brother->left = nullptr;
		return a;
	}
}

pair<Node*, int> inorderSucc(Node* q, Action* curr) {
	int pos = 0;
	Node* tmp = q;
	Node* f = tmp;
	for (int i = 0; i < 3; i++) {
		if (q->action[i] && q->action[i] == curr) {
			pos = i;
			break;
		}
	}
	switch (pos) {
	case 0:
		tmp = tmp->middle1;
		break;
	case 1:
		tmp = tmp->middle2;
		break;
	case 2:
		tmp = tmp->right;
		break;
	}
	while (tmp) {
		f = tmp;
		for (int i = 0; i < 3; i++) {
			if (tmp->action[i]) {
				pos = i;
				break;
			}
		}
		switch (pos) {
		case 0:
			tmp = tmp->left;
			break;
		case 1:
			tmp = tmp->middle1;
			break;
		case 2: 
			tmp = tmp->middle2;
			break;
		}
	}
	return { f, pos };
}

void Tree234::deleteFromTree(Node* q, int pos) {
	Node* lr = nullptr;
	bool leaf;
	leaf = !q->left && !q->middle1 && !q->middle2 && !q->right;

if(!leaf) {
	//find inorder successor of action and swap two actions
	Action* curr = q->action[pos];
	pair<Node*, int> succ = inorderSucc(q, curr);
	Action* tmpAction;
	int tmpPos;

	tmpAction = curr;
	q->action[pos] = succ.first->action[succ.second];
	pos = succ.second;
	succ.first->action[succ.second] = tmpAction;
	q = succ.first;
}
 
		/*Action* deletedAction = deleteLeaf(q, pos);
		if(deletedAction)
			delete deletedAction;*/
		if (pos == 0) { //removing red node
			//delete q->action[0];
			q->action[0] = nullptr;
			q->cnt--;
			return;
		}
		else if (pos == 2) { //removing red node
			//delete q->action[2];
			q->action[2] = nullptr;
			q->cnt--;
			return;
		}
		else { //pos == 1 => removing black node
			if (q->cnt == 3) { //node is full (3 actions)
				//delete q->action[1];
				q->action[1] = q->action[2];
				q->action[2] = nullptr;
				q->cnt--;
				return;
			}
			else if (q->cnt == 2) { //node is semi-full (2 actions)
				//delete q->action[1];
				if (q->action[0]) {
					q->action[1] = q->action[0];
					q->action[0] = nullptr;
				}
				else if (q->action[2]) {
					q->action[1] = q->action[2];
					q->action[2] = nullptr;
				}
				q->cnt--;
				return;
			}
			else { //there's only one action which is being deleted
				Action* deletingAction = q->action[1];
				while (true) {
					Node* parent = q->parent;
					if (!parent) {
						//delete q;
						root = lr;
						if (lr && lr->parent)
							lr->parent = nullptr;
						height--;
						return;
					}
					//cout << *deletingAction;
					int id = findIndexOfParent(parent, q);
					pair <Node*, int> left = getLeft(parent, id);
					pair <Node*, int> right = getRight(parent, id);
					if (left.first == q) { //we're deleting left son
						if (right.first != parent) { //real brother
							Node* brother = right.first;
							if (brother->cnt > 1) { //brother can share
								if (brother->cnt == 3) { //brother is full
									//
									Node* bl, * bm1, * bm2, * br;
									bl = brother->left;
									bm1 = brother->middle1;
									bm2 = brother->middle2;
									br = brother->right;
									//
									q->action[1] = nullptr;
									q->cnt--;
									insertInZero(parent->action[id], q, lr, bl);
									parent->action[id] = brother->action[1];
									Action* leftBrotherAction = getMinAction(brother);
									Action* rightBrotherAction = getMaxAction(brother);
									insertInOne(leftBrotherAction, q, bl, bm1);
									brother->action[1] = nullptr;
									brother->cnt--;
									insertInZero(rightBrotherAction, brother, bm2, br);
									//delete deletingAction;
									return;
								}
								else { //brother is not full
									Node* bl, * bm1, * bm2, * br;
									bl = brother->left;
									bm1 = brother->middle1;
									bm2 = brother->middle2;
									br = brother->right;

									Node* transfer = brother->action[0] ? bl : bm1;

									//q->action[1] = parent->action[id];
									q->action[1] = nullptr;
									q->cnt--;
									insertInZero(parent->action[id], q, lr, transfer);
									Action* minAction = getMinAction(brother); //finds minimum priority and updates actions
									parent->action[id] = minAction;
									//delete deletingAction;
									return;
								}
							}
							else { //brother can't share
								Node* bl = brother->middle1;
								Node* br = brother->middle2;
								Action* bAction = getMaxAction(brother);
								insertInZero(parent->action[id], brother, lr, bl);
								insertInOne(bAction, brother, bl, br);
								if (parent->cnt == 1) { //PROPAGATION!!!
									if (parent == root) {
										root = brother;
										root->parent = nullptr;
										//delete parent;
										height--;
										return;
									}
									else {
										deletingAction = parent->action[1];
										lr = brother;
										q = parent;
									}
								}
								else {
									parent->action[id] = nullptr;
									parent->cnt--;
									switch (id) {
									case 0:
										parent->left = nullptr;
										parent->middle1 = brother;
										break;
									case 1:
										parent->middle1 = nullptr;
										parent->middle2 = brother;
										break;
									case 2:
										parent->middle1 = nullptr;
										parent->middle2 = brother;
										break;
									}
									//delete q;
									return;
								}
								//cout << "BRAT JE DESNI";
								//delete q;
							}
						}
						else { //cousin, not real brother
							Node* cousin = right.first->middle2;
							if (cousin->cnt == 1) { //can't transfer to brother
								//delete q;
								parent->middle1 = nullptr;
								Node* middle1 = parent->middle2;
								Node* middle2 = parent->right;
								Node* right = nullptr, * left = nullptr;
								Action* droppingAction = getMinAction(parent);
								Node* cl = cousin->middle1;
								Node* cr = cousin->middle2;
								Action* cAction = getMinAction(cousin);
								insertInZero(droppingAction, cousin, lr, cl);
								insertInOne(cAction, cousin, cl, cr);
								parent->left = left;
								parent->middle1 = middle1;
								parent->middle2 = middle2;
								parent->right = right;
								return;
							}
							else if (cousin->cnt == 2) { //transfers one action
								Node* left = q;
								Node* middle1 = cousin;
								Node* middle2 = parent->right;
								Node* right = nullptr;
								Node* transfer = cousin->action[0] ? cousin->left : cousin->middle1;
								Action* minCous = getMinAction(cousin);
								Action* droppingAction = getMinAction(parent);
								insertInOne(minCous, parent, q, cousin);
								q->action[1] = nullptr;
								q->cnt--;
								insertInZero(droppingAction, q, lr, transfer);
								parent->left = left;
								parent->middle1 = middle1;
								parent->middle2 = middle2;
								parent->right = right;
								return;
							}
							else {
								Node* left = q;
								Node* middle1 = cousin;
								Node* middle2 = parent->right;
								Node* right = nullptr;
								Node* cl, * cm1, * cm2, * cr;
								cl = cousin->left;
								cm1 = cousin->middle1;
								cm2 = cousin->middle2;
								cr = cousin->right;
								Action* minCous = getMinAction(cousin);
								Action* risingAction = getMinAction(cousin);
								Action* droppingAction = getMinAction(parent);
								insertInOne(risingAction, parent, q, cousin);
								q->action[1] = nullptr;
								q->cnt--;
								insertInZero(droppingAction, q, lr, cl);
								insertInOne(minCous, q, cl, cm1);
								parent->left = left;
								parent->middle1 = middle1;
								parent->middle2 = middle2;
								parent->right = right;
								return;
							}
						}
					}
					/*
					*
					*
					ALMOST IDENTICAL, BUT AS IF IT'S MIRRORED
					*
					*
					*/
					else if (right.first == q) { //we're deleting right son
						if (left.first != parent) { //real brother
							Node* brother = left.first;
							if (brother->cnt > 1) { //brother can share
								if (brother->cnt == 3) { //brother is full
									Node* bl, * bm1, * bm2, * br;
									bl = brother->left;
									bm1 = brother->middle1;
									bm2 = brother->middle2;
									br = brother->right;
									//q->action[1] = parent->action[id];
									q->action[1] = nullptr;
									q->cnt--;
									insertInZero(parent->action[id], q, br, lr);
									parent->action[id] = brother->action[1];
									Action* leftBrotherAction = getMinAction(brother);
									Action* rightBrotherAction = getMaxAction(brother);
									insertInOne(rightBrotherAction, q, bm2, br);
									brother->action[1] = leftBrotherAction;
									brother->middle1 = bl;
									brother->middle2 = bm1;
									//delete deletingAction;
									return;
								}
								else { //brother is not full
									Node* bl, * bm1, * bm2, * br;
									bl = brother->left;
									bm1 = brother->middle1;
									bm2 = brother->middle2;
									br = brother->right;
									Node* transfer = brother->action[2] ? br : bm2;
									//q->action[1] = parent->action[id];
									q->action[1] = nullptr;
									q->cnt--;
									insertInZero(parent->action[id], q, transfer, lr);
									Action* maxAction = getMaxAction(brother); //finds maximum priority and updates actions
									parent->action[id] = maxAction;
									//delete deletingAction;
									return;
								}
							}
							else { //brother can't share
								Node* bl = brother->middle1;
								Node* br = brother->middle2;
								Action* bAction = getMaxAction(brother);
								insertInZero(parent->action[id], brother, br, lr);
								insertInOne(bAction, brother, bl, br);
								if (parent->cnt == 1) { //PROPAGATION!!!
									if (parent == root) {
										root = brother;
										root->parent = nullptr;
										height--;
										//delete parent;
										return;
									}
									else {
										deletingAction = parent->action[1];
										lr = brother;
										q = parent;
									}
								}
								else {
									parent->action[id] = nullptr;
									parent->cnt--;
									switch (id) {
									case 0:
										parent->left = brother;
										parent->middle1 = nullptr;
										break;
									case 1:
										parent->middle1 = brother;
										parent->middle2 = nullptr;
										break;
									case 2:
										parent->middle1 = brother;
										parent->middle2 = nullptr;
										break;
									}
									//delete q;
									return;
								}
								//cout << "BRAT JE LEVI";
							}
						}
						else { //cousin, not real brother
							Node* cousin = left.first->middle1;
							if (cousin->cnt == 1) { //can't transfer to brother
								//delete q;
								parent->middle2 = nullptr;
								Node* middle1 = parent->left;
								Node* middle2 = parent->middle1;
								Node* right = nullptr, * left = nullptr;
								Action* droppingAction = getMaxAction(parent);
								Node* cl = cousin->middle1;
								Node* cr = cousin->middle2;
								Action* cAction = getMinAction(cousin);
								insertInZero(droppingAction, cousin, cr, lr);
								insertInOne(cAction, cousin, cl, cr);
								parent->left = left;
								parent->middle1 = middle1;
								parent->middle2 = middle2;
								parent->right = right;
								return;
							}
							else if (cousin->cnt == 2) { //transfers one action
								Node* left = nullptr;
								Node* middle1 = parent->left;
								Node* middle2 = cousin;
								Node* right = q;
								Node* transfer = cousin->action[2] ? cousin->right : cousin->middle2;
								Action* maxCous = getMaxAction(cousin);
								Action* droppingAction = getMaxAction(parent);
								insertInOne(maxCous, parent, cousin, q);
								q->action[1] = nullptr;
								q->cnt--;
								insertInZero(droppingAction, q, transfer, lr);
								parent->left = left;
								parent->middle1 = middle1;
								parent->middle2 = middle2;
								parent->right = right;
								return;
							}
							else {
								Node* left = nullptr;
								Node* middle1 = parent->left;
								Node* middle2 = cousin;
								Node* right = q;
								Node* cl, * cm1, * cm2, * cr;
								cl = cousin->left;
								cm1 = cousin->middle1;
								cm2 = cousin->middle2;
								cr = cousin->right;
								Action* maxCous = getMaxAction(cousin);
								Action* risingAction = getMaxAction(cousin);
								Action* droppingAction = getMaxAction(parent);
								insertInOne(risingAction, parent, cousin, q);
								q->action[1] = nullptr;
								q->cnt--;
								insertInZero(droppingAction, q, cr, lr);
								insertInOne(maxCous, q, cm2, cr);
								parent->left = left;
								parent->middle1 = middle1;
								parent->middle2 = middle2;
								parent->right = right;
								return;
							}
						}
						//if (deletingAction)
							//delete deletingAction;
					}
					else {
						cout << "ERROR!";
					}

				}
			}
		}
	
}

void Tree234::deleteMaxPriority() {
	if (!root) return;
	Node* tmp = root;
	Node* q = tmp;
	while (tmp) {
		q = tmp;
		if (tmp->action[0]) {
			tmp = tmp->left;
		}
		else if (tmp->action[1]) {
			tmp = tmp->middle1;
		}
		else if (tmp->action[2]) {
			tmp = tmp->middle2;
		}
		else {
			tmp = tmp->right;
		}
	}
	int pos = 0;
	for (int i = 0; i < 3; i++) {
		if (q->action[i]) {
			pos = i;
			break;
		}
	}
	deleteFromTree(q, pos);
}

void Tree234::printRB() {
	if (!root)
		return;
	int h = rbHeight(root);
	int lastLvl = 0;
	int maxWidth = pow(2, h) * 6;
	int spacing = maxWidth;
	Node* next = root;
	pair <Node*, int> elem;
	queue <pair<Node*, int>> q;
	queue <int> depth;
	q.push({ next, 1 });
	depth.push(lastLvl);
	while (!q.empty() && lastLvl <= h) {
		auto tmp = q.front();
		q.pop();
		next = tmp.first;
		int currDepth = depth.front();
		depth.pop();
		if (lastLvl != currDepth) {
			lastLvl = currDepth;
			cout << endl << endl;
			if (lastLvl > h) return;
			spacing = maxWidth / pow(2, lastLvl);
		}
		for (int i = 0; i < (spacing - 6) / 2; i++)
			cout << " ";

		if (tmp.first) {
			cout << " ";
			if(tmp.second & 1)
				cout << "\x1B[1m\033[90m" << setw(3) << tmp.first->action[tmp.second]->priority << tmp.first->action[tmp.second]->name[0] << "\x1B[0m";
			else
				cout << "\x1B[1m\033[31m" << setw(3) << tmp.first->action[tmp.second]->priority << tmp.first->action[tmp.second]->name[0] << "\x1B[0m";
			cout << " ";

			// ubacivanje odgovarajuceg levog i desnog
			pair <Node*, int> left = getLeft(next, tmp.second);
			pair <Node*, int> right = getRight(next, tmp.second);
			q.push(left);
			q.push(right);
			depth.push(currDepth + 1);
			depth.push(currDepth + 1);
		}
		else {
			for (int i = 0; i < 6; i++)
				cout << " ";
			q.push({ nullptr, 0 });
			q.push({ nullptr, 0 });
			depth.push(currDepth + 1);
			depth.push(currDepth + 1);
		}
		for (int i = 0; i < (spacing - 6) / 2; i++)
			cout << " ";
	}
	while (!q.empty()) q.pop();
	while (!depth.empty()) depth.pop();	
}

void Tree234::changePriority(string name, int priority) {
	Action* action = new Action;
	strcpy_s(action->name, name.c_str());
	action->priority = priority;
	Node* tmp = root;
	Node* q = nullptr;
	while (tmp) {
		q = tmp;
		if (inNode(tmp, action)) {
			break;
		}
		if (tmp->action[0] && *action < *tmp->action[0]) {
			tmp = tmp->left;
		}
		else if (!tmp->action[1] || tmp->action[1] && *action < *tmp->action[1]) {
			tmp = tmp->middle1;
		}
		else if (!tmp->action[2] || tmp->action[2] && *action < *tmp->action[2]) {
			tmp = tmp->middle2;
		}
		else {
			tmp = tmp->right;
		}
	}
	if (!q) {
		cout << "Akcija ne postoji u stablu." << endl;
		delete action;
	}
	else {
		cout << "Unesite novi prioritet akcije: ";
		int newPrio;
		cin >> newPrio; bool leaf = !q->left && !q->middle1 && !q->middle2 && !q->right;
		int pos = 0;
		for (int i = 0; i < 3; i++) {
			if (q->action[i] && *q->action == action) {
				pos = i;
				break;
			}
		}
		deleteFromTree(q, pos);
		action->priority = newPrio;
		insertAction(action);
	}
}

int Tree234::findNumberOfActions(int priority) {
	// uradi inorder!!!
	Node* next = root;
	int cnt = 0;
	queue <Node*> q;
	if (next)
		q.push(next);
	while (!q.empty()) {
		next = q.front();
		q.pop();
		for (int i = 0; i < 3; i++) {
			if (next->action[i] && next->action[i]->priority == priority)
				cnt++;
		}
		if (next->left)
			q.push(next->left);
		if (next->middle1)
			q.push(next->middle1);
		if (next->middle2)
			q.push(next->middle2);
		if (next->right)
			q.push(next->right);
	}
	return cnt;
}
