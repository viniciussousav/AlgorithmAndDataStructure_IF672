#include <bits/stdc++.h>
#define endl '\n'


using namespace std;



class Graph
{
    int v;
    bool *visitados;
public:
    vector<int> *listaAdjacencia;
    Graph (int v);
    bool bfs(int v, int s);
};

Graph::Graph(int v)
{
    this->v = v*v;
    this->listaAdjacencia = new vector<int>[v*v];
    this->visitados = new bool[v*v];
}

bool Graph::bfs(int e, int s) {

    queue<int> fila;

    if(e == s)
        return true;

    for(int i = 0; i < this->v; i++)
        visitados[i] = false;

    visitados[e] = true;

    while(true)
    {
        for(auto & it: listaAdjacencia[e])
        {
            if(!visitados[it])
            {
                visitados[it] = true;

                if(it == s || e == s){
                    return true;
                }

                fila.push(it);
            }
        }

        if(!fila.empty())
        {
            e = fila.front();
            fila.pop();
        }
        else{
            return false;
        }
    }
}

int main(int argc, char *argv[]) {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k,n, m, q;
    cin >> k;

    Graph*grafo;

    for (int i = 0; i < k; ++i) { //NÚMERO DE CASOS

        cin >> n >> m >> q;

        grafo = new Graph(n);

        for (int j = 0; j < m; ++j) { //RETIRANDO PAREDES
            int w;
            cin >> w;
            int v = (2*(n-1)) + 1;
            if(w%v < n - 1){
                int x = ((w/v) * n) + (w % v);
                grafo->listaAdjacencia[x].push_back(x+1);
                grafo->listaAdjacencia[x+1].push_back(x);
            } else {
                int x = ((w/v) * n) + ((w % v) + 1);
                grafo->listaAdjacencia[x].push_back(x-n);
                grafo->listaAdjacencia[x-n].push_back(x);            }
        }

        for (int l = 0; l < q; ++l) { //TESTANDO CAMINHOS
            int a, b;
            cin >> a >> b;
            cout << i << "." << l << " " << grafo->bfs(a, b) << endl;

        }
        cout << endl;
    }

    return 0;
}
