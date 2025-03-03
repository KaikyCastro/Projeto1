#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <unordered_map>
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
            lerArquivo();
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
        
                somaTempoEspera += tempoAtual - aux->getTempoDeChegada();
                tempoAtual += aux->getTempoDeExecucao();
        
                filaDeProcessos.erase(aux);
            }
        
            return somaTempoEspera / numProcessos;
            
        }
};

class SJF : public Processos {
    private:
        vector<Processos> filaDeProcessos;

    public:
        SJF() : Processos() {
            lerArquivo();
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
        float tempoDeRetornoMedio() {
            vector<Processos> filaDeProcessos = this->filaDeProcessos;
            float somaTempoRetorno = 0;
            int numProcessos = filaDeProcessos.size();
            int tempoAtual = 0;
            vector<Processos> prontos; // Fila de processos que já chegaram
        
            // Ordena inicialmente pelo tempo de chegada
            sort(filaDeProcessos.begin(), filaDeProcessos.end(),
                []( Processos& a,  Processos& b) {
                    return a.getTempoDeChegada() < b.getTempoDeChegada();
                });
        
            while (!filaDeProcessos.empty() || !prontos.empty()) {
                // Adiciona processos que já chegaram na fila de prontos
                while (!filaDeProcessos.empty() && filaDeProcessos.front().getTempoDeChegada() <= tempoAtual) {
                    prontos.push_back(filaDeProcessos.front());
                    filaDeProcessos.erase(filaDeProcessos.begin()); // Remove da fila de processos
                }
        
                // Se não há processos prontos, avançar no tempo para o próximo que chega
                if (prontos.empty()) {
                    tempoAtual = filaDeProcessos.front().getTempoDeChegada();
                    continue;
                }
        
                // Encontrar o processo com menor tempo de execução na fila de prontos
                auto aux = min_element(prontos.begin(), prontos.end(),
                    []( Processos& a, Processos& b) {
                        return a.getTempoDeExecucao() < b.getTempoDeExecucao();
                    });
        
                // Calcular tempo de retorno
                somaTempoRetorno += tempoAtual + aux->getTempoDeExecucao() - aux->getTempoDeChegada();
                tempoAtual += aux->getTempoDeExecucao();
        
                // Remover o processo executado da fila de prontos
                prontos.erase(aux);
            }

        return somaTempoRetorno / numProcessos;
        }

        float tempoDeRespostaMedio() {
            vector<Processos> filaDeProcessos = this->filaDeProcessos; // Cópia da fila original
            float somaTempoResposta = 0;
            int numProcessos = filaDeProcessos.size();
            int tempoAtual = 0;
            vector<Processos> prontos; // Fila de processos que já chegaram
        
            // Ordena inicialmente pelo tempo de chegada
            sort(filaDeProcessos.begin(), filaDeProcessos.end(),
                []( Processos& a,  Processos& b) {
                    return a.getTempoDeChegada() < b.getTempoDeChegada();
                });
        
            while (!filaDeProcessos.empty() || !prontos.empty()) {
                // Adiciona processos que já chegaram na fila de prontos
                while (!filaDeProcessos.empty() && filaDeProcessos.front().getTempoDeChegada() <= tempoAtual) {
                    prontos.push_back(filaDeProcessos.front());
                    filaDeProcessos.erase(filaDeProcessos.begin()); // Remove da fila de processos
                }
        
                // Se não há processos prontos, avançar no tempo para o próximo que chega
                if (prontos.empty()) {
                    tempoAtual = filaDeProcessos.front().getTempoDeChegada();
                    continue;
                }
        
                // Encontrar o processo com menor tempo de execução na fila de prontos
                auto aux = min_element(prontos.begin(), prontos.end(),
                    []( Processos& a, Processos& b) {
                        return a.getTempoDeExecucao() < b.getTempoDeExecucao();
                    });
        
                // Calcular tempo de resposta
                somaTempoResposta += tempoAtual - aux->getTempoDeChegada();
                tempoAtual += aux->getTempoDeExecucao();
        
                // Remover o processo executado da fila de prontos
                prontos.erase(aux);
            }
        
            return somaTempoResposta / numProcessos;
        }
        

        float tempoDeEsperaMedio() {
            vector<Processos> filaDeProcessos = this->filaDeProcessos; // Cópia da fila original
            float somaTempoEspera = 0;
            int numProcessos = filaDeProcessos.size();
            int tempoAtual = 0;
            vector<Processos> prontos; // Fila de processos que já chegaram
        
            // Ordena inicialmente pelo tempo de chegada
            sort(filaDeProcessos.begin(), filaDeProcessos.end(),
                []( Processos& a,  Processos& b) {
                    return a.getTempoDeChegada() < b.getTempoDeChegada();
                });
        
            while (!filaDeProcessos.empty() || !prontos.empty()) {
                // Adiciona processos que já chegaram na fila de prontos
                while (!filaDeProcessos.empty() && filaDeProcessos.front().getTempoDeChegada() <= tempoAtual) {
                    prontos.push_back(filaDeProcessos.front());
                    filaDeProcessos.erase(filaDeProcessos.begin()); // Remove da fila de processos
                }
        
                // Se não há processos prontos, avançar no tempo para o próximo que chega
                if (prontos.empty()) {
                    tempoAtual = filaDeProcessos.front().getTempoDeChegada();
                    continue;
                }
        
                // Encontrar o processo com menor tempo de execução na fila de prontos
                auto aux = min_element(prontos.begin(), prontos.end(),
                    []( Processos& a, Processos& b) {
                        return a.getTempoDeExecucao() < b.getTempoDeExecucao();
                    });

                // Calcular tempo de espera
                somaTempoEspera += tempoAtual - aux->getTempoDeChegada();
                tempoAtual += aux->getTempoDeExecucao();
        
                // Remover o processo executado da fila de prontos
                prontos.erase(aux);
            }
        
            return somaTempoEspera / numProcessos;

        }
};


class RoundRobin : public Processos {
    private:
        float quantum;
        vector<Processos> filaDeProcessos;
    public:
        RoundRobin() : Processos() {
            this->quantum = 2;
            lerArquivo();
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
        float tempoDeRetornoMedio() {
            vector<Processos> filaDeProcessos = this->filaDeProcessos; // Cópia da fila original
            float somaTempoRetorno = 0;
            float numProcessos = filaDeProcessos.size();
            float tempoAtual = 0;
            float quantum = 2; // Defina o quantum do Round Robin
            queue<Processos> prontos; // Fila circular de processos
        
            // Ordena inicialmente pelo tempo de chegada
            sort(filaDeProcessos.begin(), filaDeProcessos.end(),
                []( Processos& a, Processos& b) {
                    return a.getTempoDeChegada() < b.getTempoDeChegada();
                });
        
            // Índice para controle de processos que entram na fila
            int index = 0;
            vector<int> temposDeConclusao(numProcessos, 0); // Armazena o tempo de conclusão de cada processo
        
            while (index < numProcessos || !prontos.empty()) {
                // Adiciona processos que chegaram à fila de prontos
                while (index < numProcessos && filaDeProcessos[index].getTempoDeChegada() <= tempoAtual) {
                    prontos.push(filaDeProcessos[index]);
                    index++;
                }
        
                // Se a fila está vazia, avançar o tempo para o próximo processo
                if (prontos.empty()) {
                    tempoAtual = filaDeProcessos[index].getTempoDeChegada();
                    continue;
                }
        
                // Pega o primeiro processo da fila
                Processos processoAtual = prontos.front();
                prontos.pop(); // Remove da fila
        
                // Executa pelo quantum ou pelo tempo restante, o que for menor
                float tempoExecutado = min(quantum, processoAtual.getTempoDeExecucao());
                tempoAtual += tempoExecutado;
                processoAtual.setTempoDeExecucao(processoAtual.getTempoDeExecucao() - tempoExecutado);
        
                // Se o processo terminou, calcula o tempo de retorno
                if (processoAtual.getTempoDeExecucao() == 0) {
                    float tempoConclusao = tempoAtual;
                    somaTempoRetorno += tempoConclusao - processoAtual.getTempoDeChegada();
                } else {
                    // Se ainda não terminou, volta para o final da fila
                    prontos.push(processoAtual);
                }
            }
        
            return somaTempoRetorno / numProcessos;
        }
        
        float tempoDeRespostaMedio() {
            vector<Processos> filaDeProcessos = this->filaDeProcessos; // Cópia da fila original
            float numProcessos = filaDeProcessos.size();
            float quantum = 2; // Quantum do Round Robin
            float tempoAtual = 0;
            queue<float> prontos; // Armazena índices dos processos
            unordered_map<float, float> tempoPrimeiraExecucao; // Índice -> Tempo da primeira execução
            vector<float> tempoRestante(numProcessos); // Tempo restante para cada processo
        
            // Ordena processos pelo tempo de chegada
            sort(filaDeProcessos.begin(), filaDeProcessos.end(),
                []( Processos& a, Processos& b) {
                    return a.getTempoDeChegada() < b.getTempoDeChegada();
                });
        
            for (int i = 0; i < numProcessos; i++) {
                tempoRestante[i] = filaDeProcessos[i].getTempoDeExecucao();
            }
        
            int index = 0;
            while (index < numProcessos || !prontos.empty()) {
                // Adicionar processos que chegaram
                while (index < numProcessos && filaDeProcessos[index].getTempoDeChegada() <= tempoAtual) {
                    prontos.push(index);
                    index++;
                }
        
                if (prontos.empty()) {
                    tempoAtual = filaDeProcessos[index].getTempoDeChegada();
                    continue;
                }
        
                int i = prontos.front(); // Pega o índice do processo
                prontos.pop();
        
                // Registra a primeira execução (se ainda não foi registrado)
                if (tempoPrimeiraExecucao.find(i) == tempoPrimeiraExecucao.end()) {
                    tempoPrimeiraExecucao[i] = tempoAtual;
                }
        
                float tempoExecutado = min(tempoRestante[i], quantum);
                tempoAtual += tempoExecutado;
                tempoRestante[i] -= tempoExecutado;
        
                if (tempoRestante[i] > 0) {
                    prontos.push(i); // Volta para a fila se ainda não terminou
                }
            }
        
            float somaTempoResposta = 0;
            for (int i = 0; i < numProcessos; i++) {
                somaTempoResposta += tempoPrimeiraExecucao[i] - filaDeProcessos[i].getTempoDeChegada();
            }
        
            return somaTempoResposta / numProcessos;
        }
        
        float tempoDeEsperaMedio() {
            vector<Processos> filaDeProcessos = this->filaDeProcessos;
            float numProcessos = filaDeProcessos.size();
            float quantum = 2;
            float tempoAtual = 0;
            queue<float> prontos;
            vector<float> tempoRestante(numProcessos);
            vector<float> tempoConclusao(numProcessos, 0);
        
            // Ordena processos pelo tempo de chegada
            sort(filaDeProcessos.begin(), filaDeProcessos.end(),
                [](Processos& a, Processos& b) {
                    return a.getTempoDeChegada() < b.getTempoDeChegada();
                });
        
            for (int i = 0; i < numProcessos; i++) {
                tempoRestante[i] = filaDeProcessos[i].getTempoDeExecucao();
            }
        
            int index = 0;
            while (index < numProcessos || !prontos.empty()) {
                while (index < numProcessos && filaDeProcessos[index].getTempoDeChegada() <= tempoAtual) {
                    prontos.push(index);
                    index++;
                }
        
                if (prontos.empty()) {
                    tempoAtual = filaDeProcessos[index].getTempoDeChegada();
                    continue;
                }
        
                float i = prontos.front();
                prontos.pop();
        
                float tempoExecutado = min(tempoRestante[i], quantum);
                tempoAtual += tempoExecutado;
                tempoRestante[i] -= tempoExecutado;
        
                if (tempoRestante[i] == 0) {
                    tempoConclusao[i] = tempoAtual;
                } else {
                    prontos.push(i);
                }
            }
        
            float somaTempoEspera = 0;
            for (int i = 0; i < numProcessos; i++) {
                float tempoRetorno = tempoConclusao[i] - filaDeProcessos[i].getTempoDeChegada();
                somaTempoEspera += tempoRetorno - filaDeProcessos[i].getTempoDeExecucao();
            }
        
            return somaTempoEspera / numProcessos;
        }    
};