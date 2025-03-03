#include "Escalonador.h"

using namespace std;

int main() {

    FCFS fcfs;
    fcfs.lerArquivo();
    //fcfs.exibirFila();
    float tResM = fcfs.tempoDeRespostaMedio();
    float tEspM = fcfs.tempoDeEsperaMedio();
    float tRetM = fcfs.tempoDeRetornoMedio();
    cout << setprecision(1) << fixed;
    cout << "Tempo de resposta: " << tResM << endl;
    cout << "Tempo de retorno: " << tEspM << endl;
    cout << "Tempo de espera: " << tRetM << endl;
    //fcfs.exibirFila();


    /* Saída:
    cout << "FCFS " << tempodeRetornoMedio << " " << tempoDeRespostaMedio << " " << tempoDeEsperaMedio << endl;
    cout << "SJF " << tempodeRetornoMedio << " " << tempoDeRespostaMedio << " " << tempoDeEsperaMedio << endl;
    cout << "RR " << tempodeRetornoMedio << " " << tempoDeRespostaMedio << " " << tempoDeEsperaMedio << endl;
    */
    return 0;
}