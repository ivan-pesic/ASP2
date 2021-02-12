#include "avl.hpp"

int treeDepth(treeNode* root) {
    if (!root)
        return 0;
    queue <treeNode*> q;
    treeNode* next = root;
    int depth = 0;
    q.push(next);

    while (true) {
        int cnt = q.size();
        if (!cnt)
            return depth;
        depth++;
        
        while (cnt) {
            treeNode* next = q.front();
            q.pop();
            if (next->left)
                q.push(next->left);
            if (next->right)
                q.push(next->right);
            cnt--;
        }
    }
}

void printTree(treeNode* tree) {
    if (!tree)   return;
    queue <qNode> q;

    int height = treeDepth(tree);

    int lastLvl = 0;

    int spacing = pow(2, height);
    int prevSpacing = spacing;

    treeNode* next = tree;
    bool flag = true;
    q.push({ next, lastLvl });

    while (!q.empty() && lastLvl <= height) {
        qNode tmp = q.front();
        q.pop();
        if (lastLvl != abs(tmp.level)) {
            cout << endl << endl;
            lastLvl = abs(tmp.level);
            if (lastLvl > height) return;
            prevSpacing = spacing;
            spacing /= 2;

            if (spacing <= 3) {
                for (int i = 0; i < prevSpacing - 2/*1*/; i++) // !
                    cout << " ";
                flag = true;
            }

        }
        if (spacing > 3)
            for (int i = 0; i < spacing; i++)
                cout << " ";

        if (tmp.node) {
            flag = !flag;
            cout << setw(3) << tmp.node->key;
            q.push({ tmp.node->left , lastLvl + 1 });
            q.push({ tmp.node->right, lastLvl + 1 });

        }
        else {
            flag = !flag;
            cout << "   ";
            q.push({ nullptr, lastLvl + 1 });
            q.push({ nullptr, lastLvl + 1 });
        }
        if (spacing > 3)
            for (int i = 0; i < spacing - 3; i++) cout << " ";
        else
            cout << " "; // !
            /*if (flag)
                cout << "  ";*/
    }
    while (!q.empty()) q.pop();
}