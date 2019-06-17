#include <bits/stdc++.h>
#define endl '\n'

using namespace std;


struct No{
    int senhaMagistrado;
    int horasProcesso;
    int empresa;
    int posInicial;
    No *proximo;
    No(int senhaMagistrado,int horasProcesso, int empresa, int posInicial): senhaMagistrado(senhaMagistrado),horasProcesso(horasProcesso), empresa(empresa), posInicial(posInicial){}

};

struct Fila{

    int quantNo = 0;
    No *head;
    No *tail;

    Fila(): head(nullptr),tail(nullptr){}

    void inserirNoFim(No *novo){

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

    Pilha(): top(new No(0,0,0,0)){}

    void empilhar(No *novo){
        if(!this->top->proximo){
            this->top->proximo = novo;
        } else {
            novo->proximo = this->top->proximo;
            this->top->proximo = novo;
        }
        this->quantNo++;
    }

    void print() {
        No *cur = this->top->proximo;
        while (cur) {
            cout << "(" << cur->senhaMagistrado << "," << cur->horasProcesso  << ")" << " ";
            cur = cur->proximo;
        }
    }

    No *pop() {

        No *excluido = this->top->proximo;
        if (this->quantNo == 1) {
            this->top->proximo = nullptr;
        } else if(this->quantNo > 1) {
            this->top->proximo = this->top->proximo->proximo;
        }
        this->quantNo -= 1;
        excluido->proximo = nullptr;
        return excluido;
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
            No *novo = new No(senhaMagistrado, horasProcesso, i, j);
            fila[i].inserirNoFim(novo);
        }
    }


    int quantMagistrados;
    cin >> quantMagistrados;

    int horasMagistradosArray[quantMagistrados];
    for (int l = 0; l < quantMagistrados; ++l) {
        cin >> horasMagistradosArray[l];
    }

    int processosTotal = 0;
    for (int m = 0; m < quantEmpresas ; ++m) {
        processosTotal += fila[m].quantNo;
    }

    Pilha *pilha = new Pilha[quantMagistrados];

    for (int k = 0, j = 0, i = 0; k < processosTotal; ) { //INSERINDO NA PILHA
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
    }



    for (int at = 0; at < quantMagistrados; ++at) { //Escolhendo o auxiliar
        for (int i = 0; i < quantMagistrados ; ++i) {
            if(i != at){
                Pilha *aux = new Pilha();
                while(pilha[at].top->proximo != nullptr) {
                    if(pilha[at].top->proximo->senhaMagistrado == i){
                        pilha[i].empilhar(pilha[at].pop());
                    } else {
                        aux->empilhar(pilha[at].pop());
                    }
                }
                pilha[at] = *aux;
            }
        }
    }

    while(processosTotal > 0){
        for (int i = 0; i < 24; ++i) {
            for (int j = 0; j < quantMagistrados; ++j) {
                if(pilha[j].top->proximo){
                    if(horasMagistradosArray[j] > i){
                        pilha[j].top->proximo->horasProcesso -= 1;
                        if(pilha[j].top->proximo->horasProcesso == 0){
                            cout << j << " " << pilha[j].top->proximo->empresa << " " << pilha[j].top->proximo->posInicial << endl;
                            pilha[j].pop();
                            processosTotal--;
                        }
                    }
                }
            }
        }
    }


}