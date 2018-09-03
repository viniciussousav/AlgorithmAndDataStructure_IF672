#include <bits/stdc++.h>
#define endl '\n'

using namespace std;


struct No{
    int senhaMagistrado;
    int horasProcesso;
    int empresa;
    No *proximo;
    No(int senhaMagistrado,int horasProcesso, int empresa): senhaMagistrado(senhaMagistrado),horasProcesso(horasProcesso), empresa(empresa){}

};

struct Fila{

    int quantNo = 0;
    No *head;
    No *tail;

    Fila(): head(nullptr),tail(nullptr){}

    void inserirNoFim(int senhaMagistrado, int horasProcesso, int empresa){
        No *novo = new No(senhaMagistrado, horasProcesso, empresa);
        if(!this->tail){
            this->head = novo;
            this->tail = novo;
        } else {
            this->tail->proximo = novo;
            this->tail = novo;
        }
        this->quantNo++;
    }

    void print() {
        No *cur = this->head;
        while (cur) {
            cout << "(" << cur->senhaMagistrado << "," << cur->horasProcesso  << ")" <<" ";
            cur = cur->proximo;
        }
    }

    No *retirarInicio() {
        No *excluido = this->head;
        if (this->quantNo == 1) {
            this->head = nullptr;
            this->tail = nullptr;
        } else if(this->quantNo > 1) {
            this->head = this->head->proximo;
        }
        this->quantNo -= 1;
        excluido->proximo = nullptr;
        return excluido;
    }
};

struct Pilha{

    int quantNo = 0;

    No *top;

    Pilha(): top(nullptr){}

    void empilhar(No *novo){
        if(!this->top){
            this->top = novo;
        } else {
            novo->proximo = this->top;
            this->top = novo;
        }
        this->quantNo++;
    }

    void print() {
        No *cur = this->top;
        while (cur) {
            cout << "(" << cur->senhaMagistrado << "," << cur->horasProcesso  << ")" << " ";
            cur = cur->proximo;
        }
    }

    void pop() {
        if (this->quantNo == 1) {
            this->top->proximo = nullptr;
        } else if(this->quantNo > 1) {
            this->top->proximo = this->top->proximo->proximo;
        }
        quantNo -= 1;
    }
};

int main(int argc, char *argv[]) {

    int quantEmpresas;
    cin >> quantEmpresas;

    Fila *fila = new Fila[quantEmpresas];

    for(int i = 0; i < quantEmpresas; i++){
        int quantProcessos;
        cin >> quantProcessos;
        for (int j = 0; j < quantProcessos; j++) {
            int senhaMagistrado;
            cin >> senhaMagistrado;
            int horasProcesso;
            cin >> horasProcesso;
            fila[i].inserirNoFim(senhaMagistrado,horasProcesso, i);
        }
    }

    for (int k = 0; k < quantEmpresas; ++k) {
        cout << "Fila " << (k+1) << ": ";
        fila[k].print();
        cout << "" << endl;
    }

    cout << "Insira a quantidade de magistrados" << endl;
    int quantMagistrados;
    cin >> quantMagistrados;

    int processosTotal = 0;
    for (int m = 0; m < quantEmpresas ; ++m) {
        processosTotal += fila[m].quantNo;
    }
    cout << "O número total de processos é: " << processosTotal << endl;

    Pilha *pilha = new Pilha[quantMagistrados];


    //INSERINDO NA PILHA
    for (int k = 0, j = 0, i = 0; k < processosTotal; ) {
        if(fila[i].quantNo > 0){
            pilha[j].empilhar(fila[i].retirarInicio());
            j++;
            k++;
        }
        i++;
        if(j == quantMagistrados){
            j = 0;
        }
        if(i == quantEmpresas){
            i = 0;
        }

    } //TERMINO IMPRESSÃO


    for (int k = 0; k < quantMagistrados; ++k) {
        cout << "Pilha " << (k+1) << ": ";
        pilha[k].print();
        cout << "" << endl;
    }


    for (int l = 0; l < quantMagistrados; ++l) {
        cout << "Topo pilha" << (l+1) << ": (" << pilha[l].top->senhaMagistrado << ", " << pilha[l].top->horasProcesso << ")" << endl;
    }
}


