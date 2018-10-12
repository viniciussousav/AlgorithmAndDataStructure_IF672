#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct paciente {

    int idade;
    int urgencia;
    int ordem;

    paciente(){}
    paciente(int idade, int urgencia, int ordem): idade(idade), urgencia(urgencia), ordem(ordem){}

};


class Heap{

public:

    int tamanho;
    int quantidade;
    int vez;

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
    void bubbleUp(int pos){

        while (pos > 0 && temPai(pos)){
            if(getPai(pos).urgencia < array[pos].urgencia){
                trocar((pos-1)/2, pos);
                pos = (pos - 1)/2;
            } else if(getPai(pos).idade < array[pos].idade && getPai(pos).urgencia == array[pos].urgencia){
                trocar((pos-1)/2, pos);
                pos = (pos - 1)/2;
            } else if(getPai(pos).ordem < array[pos].ordem && getPai(pos).idade == array[pos].idade && getPai(pos).urgencia == array[pos].urgencia){
                trocar((pos-1)/2, pos);
                pos = (pos - 1)/2;
            } else{
                pos--;
            }
        }
    }
    void heapify(int pos) {

        int index = pos;
        if (temFilhoEsquerda(pos) && getFilhoEsquerda(pos).urgencia >= array[index].urgencia) {
            if (getFilhoEsquerda(pos).urgencia == this->array[index].urgencia){
                if(getFilhoEsquerda(pos).idade > this->array[index].idade){
                    index = 2*pos + 1;
                } else if(getFilhoEsquerda(pos).idade == this->array[index].idade) {
                    if(getFilhoEsquerda(pos).ordem < this->array[index].ordem){
                        index = 2*pos + 1;
                    }
                }
            } else {
                index = 2*pos + 1;
            }
        }

        if (temFilhoDireita(pos) && getFilhoDireita(pos).urgencia >= array[index].urgencia) {
            if (getFilhoDireita(pos).urgencia == this->array[index].urgencia){
                if(getFilhoDireita(pos).idade > this->array[index].idade){
                    index = 2*pos + 2;
                } else if(getFilhoDireita(pos).idade == this->array[index].idade) {
                    if(getFilhoDireita(pos).ordem < this->array[index].ordem){
                        index = 2*pos + 2;
                    }
                }
            } else {
                index = 2*pos + 2;
            }
        }

        if(index != pos){
            trocar(index, pos);
            heapify(index);
        }

    }

    void add(int idade,int urgencia){
        paciente newPaciente(idade, urgencia, this->vez);
        aumentar();
        this->array[this->quantidade] = newPaciente;
        this->quantidade++;
        this->vez++;
        bubbleUp(this->quantidade - 1);

    }
    void atender(){
        paciente atendido = this->array[0];
        this->array[0] = this->array[this->quantidade-1];
        this->quantidade--;
        heapify(0);
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
        } else if(entrada == "NXT"){
            int a;
            cin >> a;
            cout << a << " " << fila[a].at(0).idade << " " << fila[a].at(0).urgencia << endl;
            fila[a].atender();
        } else if(entrada == "STD"){
            Heap* temMenor;
            for (int i = 0; i < numeroServicos - 1; ++i) {
                if(fila[i].at(0).urgencia < fila[i + 1].at(0).urgencia){
                    temMenor = &fila[i];
                } else if (fila[i].at(0).idade < fila[i+1].at(0).idade && fila[i].at(0).urgencia == fila[i+1].at(0).urgencia){
                    temMenor = &fila[i];
                } else if (fila[i].at(0).ordem < fila[i+1].at(0).ordem && fila[i].at(0).idade == fila[i + 1].at(0).idade && fila[i].at(0).urgencia == fila[i + 1].at(0).urgencia)
            }

        }
    }


    return 0;
}