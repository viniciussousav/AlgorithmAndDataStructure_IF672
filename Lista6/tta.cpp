#include <bits/stdc++.h>
#include "list"
#define endl '\n'

using namespace std;

struct Heap {

    vector<pair<int, double>> array;

    double getPai(int pos) {
        return array[(pos - 1) / 2].second;
    }
    double getFilhoEsquerda(int pos) {
        return array[pos * 2 + 1].second;
    }
    double getFilhoDireita(int pos) {
        return array[pos * 2 + 2].second;
    }

    bool temFilhoEsquerda(int pos) {
        if (2 * pos + 1 < array.size())
            return true;
        return false;

    }
    bool temFilhoDireita(int pos) {
        if (2 * pos + 2 < array.size())
            return true;
        return false;
    }
    bool temPai(int pos) {
        if ((pos - 1) / 2 >= 0)
            return true;
        return false;

    }

    void heapifyUp(){
        int pos = this->array.size() - 1;
        while(temPai(pos) & getPai(pos) > array[pos].second){

            pair<int, double> aux = array[(pos - 1)/2];
            array[(pos - 1)/2] = array[pos];
            array[pos] = aux;
            pos = (pos - 1)/2;
        }
    }
    void heapifyDown(){ //CORRIGIR AQUI
        int pos = 0;
        while(temFilhoEsquerda(pos)){
            int menorPos = pos * 2 + 1;
            if(temFilhoDireita(pos) && getFilhoDireita(pos) < getFilhoEsquerda(pos)){
                menorPos = pos * 2 + 2;
            }

            if(array[pos].second < array[menorPos].second){
                break;
            } else {
                pair<int, double> aux = array[pos];
                array[pos] = array[menorPos];
                array[menorPos] = aux;
            }
            pos = menorPos;
        }
    }

    pair<int,double> extract(){
        if(!this->array.empty()){
            pair<int, double> deletado = this->array[0];
            this->array[0] = this->array[array.size() - 1];
            array.pop_back();
            heapifyDown();
            return deletado;
        }
    }

    void add(pair<int, double> novo){
        array.push_back(novo);
        heapifyUp();
    }

    void update(pair<int, double> update){
        for (int i = 0; i < this->array.size(); ++i) {
            if(this->array[i].first == update.first){
                this->array[i].second = update.second;
                heapifyUp();
                break;
            }
        }
        add(update);
    }
};


struct Grafo{
    int n;
    vector<pair<int, double>> *listAdj;
    double p;

    Grafo(int n, double p){
        this->listAdj = new vector<pair<int, double>>[n];
        this->n = n;
        this->p = p;
    }

    void add(int x, int y, int b, int c){
        double w = ((p*b + (1-p)*c)) / (b+c);
        this->listAdj[x].push_back({y, w});
        this->listAdj[y].push_back({x, w});
    }

    void Dijkstra(int s, int t){

        double *D = new double[this->n];
        int *F = new int[this->n];

        for (int i = 0; i < this->n; ++i){
            D[i] = INFINITY;
            F[i] = -1;
        }

        D[s] = 0;
        F[s] = s;

        Heap *H = new Heap;
        H->add({s, 0});

        while(!H->array.empty()){

            pair<int, double> aux = H->extract();

            int u = aux.first;

            vector<pair<int, double>>::iterator e;
            for (e = listAdj[u].begin(); e != listAdj[u].end() ; ++e) {
                double g = e->second;
                int k = e->first;
                if(D[k] > D[u] + g){
                    D[k] = D[u] + g;
                    F[k] = u;
                    H->update({k, D[k]});
                }
            }

        }

        vector<int> menor_caminho;
        menor_caminho.push_back(t);

        for (int j = t; F[j] != s; j = F[j]) {
            menor_caminho.push_back(F[j]);
        }

        menor_caminho.push_back(s);

        while(!menor_caminho.empty()) {
            cout << menor_caminho.back();
            menor_caminho.pop_back();

            if(!menor_caminho.empty()) {
                cout << " ";
            } else {
                cout << endl;
            }
        }

    }

};


int main(int argc, char *argv[]) {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double p;
    cin >> p;
    int m, n;
    cin >> n >> m;
    Grafo grafo(n,p);

    for (int i = 0; i < m; ++i) {
        int x, y, b, c;
        cin >> x >> y >> b >> c;
        grafo.add(x,y,b,c);
    }

    int s, t;
    while(cin >> s >> t){
        grafo.Dijkstra(s, t);
    }


    return 0;
}


