#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define endl '\n'

string hope = "";

struct node {

    int m;
    int l;
    int r;

    node *left;
    node *right;

    node(int l, int r) : l(l), r(r), left(nullptr), right(nullptr) {
    }
};

struct binaryTree {

    node *root;

    node *abinaryTree(node *memes, int array[], int l, int r) {

        memes = new node(l, r);

        if (l == r) {
            memes->m = array[r];
            return memes;

        } else {
            int h = floor((l + r) / 2);
            memes->left = abinaryTree(memes->left, array, l, h);
            memes->right = abinaryTree(memes->right, array, h + 1, r);
            memes->m = min(memes->left->m, memes->right->m);
            return memes;
        }
    }
};

void update(node *BTree, int i, int v) {

    if (BTree->l == BTree->r) {
        BTree->m = v;
    } else{
        int h = (BTree->r + BTree->l)/2;
        if(i <= h){
            update(BTree->left, i ,v);
        } else{
            update(BTree->right,i,v);
        }
        BTree->m = min(BTree->left->m, BTree->right->m);
    }
}


int f(node *BTree, int a, int b) {
    if (a > b || a > BTree->r || b < BTree->l) {
        return INT_MAX;
    } else if (a == BTree->l && b == BTree->r) {
        return BTree->m;
    } else {
        int h = (BTree->l + BTree->r) / 2;
        return min(f(BTree->left, max(a, BTree->l), min(b, h)), f(BTree->right, max(a, h + 1), min(b, BTree->r)));
    }
}

void print_pos_order(node *BTree, int a, int b) {

    if (BTree->r > BTree->l) {
        if (BTree->left->r >= a) {
            print_pos_order(BTree->left, a, b);
        }
        if (BTree->right->l <= b) {
            print_pos_order(BTree->right, a, b);
        }
    }
    hope += to_string(BTree->m) + " ";
}


int main() {

    int n;
    cin >> n;
    int array[n];
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }

    binaryTree *BT = new binaryTree;
    BT->root = BT->abinaryTree(BT->root, array, 0, n - 1);


    string entrada;
    cin >> entrada;
    while (entrada != "END") {

        if (entrada == "UPD") {
            int i, v;
            cin >> i >> v;
            update(BT->root, i, v);
        } else if (entrada == "RMQ") {
            int a, b;
            cin >> a >> b;
            cout << f(BT->root, a, b) << endl;
        } else if (entrada == "PRT") {
            hope = "";
            int a, b;
            cin >> a >> b;
            print_pos_order(BT->root, a, b);
            string print = hope.substr(0, hope.size() - 1);
            cout << print << endl;
        }
        cin >> entrada;

    }

    return 0;
}