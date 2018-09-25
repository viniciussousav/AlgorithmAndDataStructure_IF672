#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define endl '\n'


struct node{

    int *m;
    int l;
    int r;

    node(int l, int r):l(l),r(r) {
    }
};

struct binaryTree{

    node *root;


    binaryTree *left = nullptr;
    binaryTree *right = nullptr;

    binaryTree(int *array[], int l ,int r){

        this->root = new node(l,r);

        if(this->root->l == this->root->r){
            this->root->m = array[r];

        } else {
            int h = (l+r)/2;
            this->left = new binaryTree(array, l, h);
            this->right = new binaryTree(array, h+1, r);
            if(this->left->root->m < this->right->root->m){
                this->root->m = this->left->root->m;
            } else{
                this->root->m = this->right->root->m;
            }
        }
    }

    int f(int a, int b){
        if(a == this->root->l && b == this->root->r){
            return *this->root->m;
        }
        else if(a > b || a > this->root->r || b < this->root->l) {
            return 999999999;
        } else {
            int h = (this->root->l + this->root->r)/2;
            return min(this->left->f(max(a, this->root->l),min(b,h)), this->right->f( max(a, h+1),min(b,this->root->r)) );
        }
    }

    void print_pos_order(binaryTree *bt){


    }

};


int main() {


    int n;
    cin >> n;
    int *array[n];
    for (int i = 0; i < n; ++i) {
        int v;
        array[i] = new int[v];
    }

    binaryTree *BT = new binaryTree(array,0,n);

    cout << *BT->root->m << endl;

    string entrada;
    cin >> entrada;
    while(entrada != "END"){
        if(entrada == "UPD"){
            int i;
            int v;
            cin >> i >> v;
            array[i] = new int[v];
        } else if(entrada == "RQM") {
            int a, b;
            cin >> a >> b;
            cout << BT->f(a, b) << endl;
        } else if(entrada == "PRT"){
            int a,b;
            cin >> a >> b;
        }

        cin >> entrada;
    }

    return 0;
}