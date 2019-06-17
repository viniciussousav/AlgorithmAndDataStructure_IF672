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

    paciente* array;

    Heap(){
        this->array = nullptr;
        this->tamanho = 1;
        this->quantidade = 0;
        this->array = new paciente[tamanho];
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
            } else if(getPai(pos).idade < array[pos].idade && getPai(pos).urgencia == array[pos].urgencia){
                trocar((pos-1)/2, pos);
            } else if(getPai(pos).ordem < array[pos].ordem && getPai(pos).idade == array[pos].idade && getPai(pos).urgencia == array[pos].urgencia) {
                trocar((pos - 1) / 2, pos);
            }
            pos = (pos - 1)/2;

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

    void add(int idade,int urgencia, int ordem){
        paciente newPaciente(idade, urgencia, ordem);
        this->array[this->quantidade] = newPaciente;
        this->quantidade++;
        bubbleUp(this->quantidade - 1);
        aumentar();

    }

    paciente atender(){
        paciente atendido = this->array[0];
        if(this->quantidade > 0){
            this->array[0] = this->array[this->quantidade-1];
            this->quantidade--;
            heapify(0);
        }
        return atendido;

    }

    paciente at(int i){
        return array[i];
    }

};



int main(int argc, char *argv[]) {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numeroServicos;
    cin >> numeroServicos;

    Heap  fila [numeroServicos];

    int ordem = 0;
    string entrada;
    while(cin >> entrada, entrada != "END"){
        if(entrada == "CIN"){
            int idade, urgencia, servico;
            cin >> idade >> urgencia >> servico;
            fila[servico].add(idade, urgencia, ordem); //já estou adicionando
            ordem++;
        } else if(entrada == "NXT"){
            int a;
            cin >> a;
            paciente retirado = fila[a].atender();
            cout << a << " " << retirado.idade << " " << retirado.urgencia << endl;
        } else if(entrada == "STD"){
            int indice = 0;
            for (int i = 1; i < numeroServicos; ++i) {
                if(fila[indice].quantidade == 0 && fila[i].quantidade > 0){
                    indice = i;
                } else if (fila[indice].quantidade > 0 && fila[i].quantidade > 0){
                    if(fila[indice].at(0).urgencia > fila[i].at(0).urgencia){
                        indice = i;
                    } else if (fila[indice].at(0).idade > fila[i].at(0).idade && fila[indice].at(0).urgencia == fila[i].at(0).urgencia){
                        indice = i;
                    } else if (fila[indice].at(0).ordem > fila[i].at(0).ordem && fila[indice].at(0).idade == fila[i].at(0).idade && fila[indice].at(0).urgencia == fila[i].at(0).urgencia){
                        indice = i;
                    }
                }

            }

            if(fila[indice].quantidade == 0){
                cout << "-1 -1 -1" << endl;
            } else {
                cout << indice << " " << fila[indice].at(0).idade << " " << fila[indice].at(0).urgencia << endl;
                fila[indice].atender();

            }

        }
    }


    return 0;
}