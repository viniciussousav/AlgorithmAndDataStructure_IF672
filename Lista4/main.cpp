#include <bits/stdc++.h>
#define endl '\n'

using namespace std;




class Heap{

public:

    int tamanho;
    int quantidade;

    struct paciente {

        int idade;
        int urgencia;
        int servico;

        paciente(){}

        paciente(int idade, int urgencia, int servico): idade(idade), urgencia(urgencia), servico(servico){}
    };

    paciente* array;


    Heap(){
        this->array = nullptr;
        this->tamanho = 1;
        this->quantidade = 0;
        this->array = new paciente[tamanho];
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

    void add(paciente newPaciente){
        this->array[this->quantidade] = newPaciente;
        this->quantidade++;
        this->aumentar();
    }

    paciente at(int i){
        return array[i];
    }


};


int main(int argc, char *argv[]) {

    Heap *hospital = new Heap();

    for (int i = 0; i < 5; ++i) {
        int idade, urgencia, servico;
        cin >> idade >> urgencia >> servico;
        paciente novoPaciente(idade, urgencia, servico);
        hospital->add(novoPaciente);
    }

    for (int j = 0; j < hospital->quantidade; ++j) {
        cout << "Idade: " << hospital->at(j).idade  <<" | Urgencia: " << hospital->at(j).urgencia << endl;
    }
    return 0;
}
