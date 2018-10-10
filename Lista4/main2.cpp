#include <bits/stdc++.h>
#define endl '\n'

using namespace std;




class Heap{

public:

    int tamanho;
    int quantidade;
    int vez;

    struct paciente {

        int idade;
        int urgencia;
        int ordem;

        paciente(){}
        paciente(int idade, int urgencia, int ordem): idade(idade), urgencia(urgencia), ordem(ordem){}

    };

    paciente* array;

    Heap(){
        this->array = nullptr;
        this->tamanho = 1;
        this->quantidade = 0;
        this->array = new paciente[tamanho];
        this->vez = 0;
    }

    bool temFilhoEsquerda(int pos){
        if(2*pos + 1 < quantidade){
            return true;
        } else {
            return false;
        }
    }
    bool temFilhoDireita(int pos){
        if(2*pos + 2 < quantidade){
            return true;
        } else {
            return false;
        }
    }
    bool temPai(int pos){
        if((pos - 1)/2 >= 0){
            return true;
        } else {
            return false;
        }
    }

    paciente getPai(int pos){
        return array[(pos-1)/2];
    }


    paciente getFilhoEsquerda(int pos){
        return array[pos*2 + 1];
    }
    paciente getFilhoDireita(int pos){
        return array[pos*2 + 2];
    }

    void aumentar(){
        if(this->tamanho==this->quantidade){
            int newtam = (tamanho*2+1);
            paciente * aux = new paciente[tamanho];

            for(int i=0;i<tamanho;i++){
                aux[i]=this->array[i];
            }

            delete[] this->array;
            this->array = nullptr;

            this->array = new paciente[newtam]();
            for(int i=0;i<tamanho;i++){
                this->array[i]=aux[i];
            }
            this->tamanho = newtam;
        }
    }

    void trocar(int posUm, int posDois){
        paciente aux = array[posUm];
        array[posUm] = array[posDois];
        array[posDois] = aux;
    }


    void heapifyUp(){
        int pos = 0;
        while (pos < this->quantidade){
            if(temPai(pos)) {
                if(getPai(pos).urgencia < array[pos].urgencia){
                    trocar((pos-1)/2, pos);
                } else if(getPai(pos).idade < array[pos].idade && getPai(pos).urgencia == array[pos].urgencia){
                    trocar((pos-1)/2, pos);
                } else if(getPai(pos).ordem < array[pos].ordem && getPai(pos).idade == array[pos].idade){
                    trocar((pos-1)/2, pos);
                }
            }
            pos++;
        }
    }

    void retirarMaior(){

    }

    void add(int idade,int urgencia){
        paciente newPaciente(idade, urgencia, this->vez);
        this->array[this->quantidade] = newPaciente;
        this->quantidade++;
        this->vez++;
        heapifyUp();
        heapifyUp();
        aumentar();
    }

    paciente at(int i){
        return array[i];
    }

};


int main(int argc, char *argv[]) {

    int numeroServicos;
    cin >> numeroServicos;

    Heap  fila [numeroServicos];

    string entrada;
    while(cin >> entrada, entrada != "END"){
        if(entrada == "CIN"){
            int idade, urgencia, servico;
            cin >> idade >> urgencia >> servico;
            fila[servico].add(idade, urgencia); //já estou adicionando
        }
    }

    for (int i = 0; i < fila[0].quantidade; ++i) {
        cout << "Urgência: " << fila[0].at(i).urgencia << ", idade: " << fila[0].at(i).idade << endl;
    }

    return 0;
}