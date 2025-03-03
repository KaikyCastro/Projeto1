#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream arquivo;

    arquivo.open("C:\\Users\\Casa\\Documents\\Faculdade\\P4\\Sistema Operacional\\Projeto1\\Numeros.txt");
    while(arquivo.good()) {
        int numero1, numero2;
        arquivo >> numero1 >> numero2;
        cout << numero1 << " " << numero2 << endl;
    }

    arquivo.close();
    return 0;
}