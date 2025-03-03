#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

class Processos {
    private:
        float tempoDeChegada;
        float tempoDeExecucao;

    public:
        Processos() {
            this->tempoDeChegada = 0;
            this->tempoDeExecucao = 0;
        }
        float getTempoDeChegada() {
            return tempoDeChegada;
        }
        float getTempoDeExecucao() {
            return tempoDeExecucao;
        }
        void setTempoDeChegada(int tempoDeChegada) {
            this->tempoDeChegada = tempoDeChegada;
        }
        void setTempoDeExecucao(int tempoDeExecucao) {
            this->tempoDeExecucao = tempoDeExecucao;
        }
};

class FCFS : public Processos {
    private:
        vector<Processos> filaDeProcessos;
    public:
        FCFS() : Processos() {
        }
        void lerArquivo() {
            ifstream arquivo;
            arquivo.open("C:\\Users\\Casa\\Documents\\Faculdade\\P4\\Sistema Operacional\\Projeto1\\Numeros.txt");

            while(arquivo.good()) {
                Processos processo;
                float tempoDeChegada, tempoDeExecucao;
                arquivo >> tempoDeChegada >> tempoDeExecucao;
                processo.setTempoDeChegada(tempoDeChegada);
                processo.setTempoDeExecucao(tempoDeExecucao);
                filaDeProcessos.push_back(processo);
            }
            arquivo.close();
        }

        void exibirFila() {
            for(auto it = filaDeProcessos.begin(); it != filaDeProcessos.end(); ++it) {
                cout << "Tempo de chegada: " << it->getTempoDeChegada() << " Tempo de execucao: " << it->getTempoDeExecucao() << endl;
            }
        }
        
        float tempoDeRetornoMedio() {   
            vector<Processos> filaDeProcessos = this->filaDeProcessos;
            float somaTempoRetorno = 0;
            int numProcessos = filaDeProcessos.size();
            int tempoAtual = 0;
        
            while (!filaDeProcessos.empty()) {
                // Encontrar o processo com o menor tempo de chegada
                auto aux = min_element(filaDeProcessos.begin(), filaDeProcessos.end(),
                    []( Processos& a, Processos& b) {
                        return a.getTempoDeChegada() < b.getTempoDeChegada();
                    });
        
                cout << "Tempo de chegada: " << aux->getTempoDeChegada()
                     << " Tempo de execucao: " << aux->getTempoDeExecucao() << endl;
        
                somaTempoRetorno += tempoAtual + aux->getTempoDeExecucao() - aux->getTempoDeChegada();
                tempoAtual += aux->getTempoDeExecucao();
        
                filaDeProcessos.erase(aux);
            }
        
            return somaTempoRetorno / numProcessos;

        }

        float tempoDeRespostaMedio() {
            vector<Processos> filaDeProcessos = this->filaDeProcessos;
            float somaTempoResposta = 0;
            int numProcessos = filaDeProcessos.size();
            int tempoAtual = 0;
        
            while (!filaDeProcessos.empty()) {
                // Encontrar o processo com o menor tempo de chegada
                auto aux = min_element(filaDeProcessos.begin(), filaDeProcessos.end(),
                    []( Processos& a, Processos& b) {
                        return a.getTempoDeChegada() < b.getTempoDeChegada();
                    });
        
                cout << "Tempo de chegada: " << aux->getTempoDeChegada()
                     << " Tempo de execucao: " << aux->getTempoDeExecucao() << endl;
        

                somaTempoResposta += tempoAtual - aux->getTempoDeChegada();
                tempoAtual += aux->getTempoDeExecucao();
        
                filaDeProcessos.erase(aux);
            }
        
            return somaTempoResposta / numProcessos;
        }
        
        float tempoDeEsperaMedio() {
            vector<Processos> filaDeProcessos = this->filaDeProcessos;
            float somaTempoEspera = 0;
            int numProcessos = filaDeProcessos.size();
            int tempoAtual = 0;
        
            while (!filaDeProcessos.empty()) {
                // Encontrar o processo com o menor tempo de chegada
                auto aux = min_element(filaDeProcessos.begin(), filaDeProcessos.end(),
                    []( Processos& a, Processos& b) {
                        return a.getTempoDeChegada() < b.getTempoDeChegada();
                    });
        
                cout << "Tempo de chegada: " << aux->getTempoDeChegada()
                     << " Tempo de execucao: " << aux->getTempoDeExecucao() << endl;
        
                somaTempoEspera += tempoAtual - aux->getTempoDeChegada();
                tempoAtual += aux->getTempoDeExecucao();
        
                filaDeProcessos.erase(aux);
            }
        
            return somaTempoEspera / numProcessos;
            
        }
};
/*
class SJF : public Processos {

    public:
        SJF() : Processos() {
        }
        int tempoDeRetornoMedio() {

        }
        int tempoDeRespostaMedio() {

        }
        int tempoDeEsperaMedio() {

        }
};

class RoundRobin : public Processos {
    private:
        int quantum;
        queue<Processos> filaDeProcessos;
    public:
        RoundRobin() : Processos() {
            this->quantum = 2;
        }
        int tempoDeRetornoMedio() {

        }
        int tempoDeRespostaMedio() {

        }
        int tempoDeEsperaMedio() {

        }
};
*/