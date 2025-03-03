#include "Escalonador.h"

using namespace std;

int main() {

    FCFS fcfs;
    SJF sjf;
    RoundRobin rr;
    
    cout << setprecision(1) << fixed;
    cout << "FCFS " << fcfs.tempoDeRetornoMedio() << " " << fcfs.tempoDeRespostaMedio() << " " << fcfs.tempoDeEsperaMedio() << endl;
    cout << "SJF " << sjf.tempoDeRetornoMedio() << " " << sjf.tempoDeRespostaMedio() << " " << sjf.tempoDeEsperaMedio() << endl;
    cout << "RR " << rr.tempoDeRetornoMedio() << " " << rr.tempoDeRespostaMedio() << " " << rr.tempoDeEsperaMedio() << endl;

    return 0;
}