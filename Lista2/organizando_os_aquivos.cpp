#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct Arquivo{

    string nome;
    int ID;
    Arquivo *proximo;

    Arquivo(string nome, int ID): nome(nome), ID(ID){}
};

struct Lista{

    int total = 0;
    Arquivo *head;
    Arquivo *tail;

    Lista(): head(new Arquivo("", 0)),tail(nullptr){}

    void inserir(Arquivo *novo){

        if(!this->head->proximo){
            this->head->proximo = novo;
            this->tail = novo;
        } else {
            this->tail->proximo = novo;
            this->tail = novo;
        }
        total++;
    }


    int retornarPos(string nome){
        Arquivo *cur = this->head->proximo;
        int count = 1;

        while (cur) {
            if(cur->nome == nome){
                return count;
            }
            count += 1;
            cur = cur->proximo;
        }
        return -1;
    }

};

int funcaoChave(string nome){

    int chave = 0;
    for (int i = 0; i < nome.length(); ++i) {
        chave += (i+1)*nome[i];
    }
    return chave;
}

int procurar(int id, Arquivo *array[], int tamanhoArray){

    int l = 0;
    int r = tamanhoArray-1;
    while (l <= r) {
        int m = (l+r)/2;
        if(array[m]->ID == id){
            return m;
        } else if (id < array[m]->ID){
            r = m-1;
        } else{
            l = m+1;
        }
    }
    return -1;
};

int main(int argc, char *argv[]) {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nGavetasAntigas;
    cin >> nGavetasAntigas;

    Arquivo *armarioAntigo[nGavetasAntigas]; //CRIANDO O ARMARIO ANTIGO

    for (int i = 0; i < nGavetasAntigas; ++i) {//inserindo os arquivos do armario antigo
        string nome;
        cin >> nome;
        int id;
        cin >> id;
        Arquivo *novo = new Arquivo(nome, id);
        armarioAntigo[i] = novo;
    }

    int nGavetasNovas;
    cin >> nGavetasNovas;

    Lista *armarioNovo = new Lista[nGavetasNovas]; //CRIANDO O ARMARIO NOVO

    int nTransferidos;
    cin >> nTransferidos;

    for (int j = 0; j < nTransferidos; ++j) {

        int idTransferido;
        cin >> idTransferido;

        if(procurar(idTransferido, armarioAntigo, nGavetasAntigas) != -1){

            int pos = procurar(idTransferido, armarioAntigo, nGavetasAntigas);
            int k = funcaoChave(armarioAntigo[pos]->nome);
            int h = k%nGavetasNovas;
            armarioNovo[h].inserir(armarioAntigo[pos]);
        }
    }

    for (int k = 0; k < nGavetasNovas; ++k) {
        cout << k << ": " << armarioNovo[k].total << endl;
    }

    int nConsultas;
    cin >> nConsultas;

    for (int i = 0; i < nConsultas; i++) {
        string nome;
        cin >> nome;
        int k = funcaoChave(nome);
        int h = k%nGavetasNovas;
        if(armarioNovo[h].retornarPos(nome) != -1) {
            cout << i << ": " << armarioNovo[h].retornarPos(nome) << endl;
        }
    }
}


