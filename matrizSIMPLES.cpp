#include <iostream>
#include <locale.h>
#include <time.h>

using namespace std;
double time1, timedif;

const int tam = 5;
// declarando as matrizes utilizadas
float matrix1[tam][tam] ={{32.5, 25.9, 36.2, 45.2, 56.8, 42.1, 37.2, 38.9, 23.7, 69.5},
                       {49.7, 86.5, 47.1, 89.2, 23.5, 32.5, 25.9, 36.2, 45.2, 56.8},
                       {72.6, 58.1, 99.8, 12.6, 77.7, 34.2, 77.5, 82.2, 43.3, 89.2},
                       {25.7, 89.2, 12.4, 44.5, 32.1, 18.6, 74.4, 76.3, 22.2, 65.3},
                       {42.1, 37.2, 38.9, 23.7, 69.5, 52.1, 77.2, 28.9, 53.7, 99.5},
                       {32.5, 25.9, 36.2, 45.2, 56.8, 72.6, 58.1, 99.8, 12.6, 77.7},
                       {49.7, 86.5, 47.1, 89.2, 23.5, 25.7, 89.2, 12.4, 44.5, 32.1},
                       {72.6, 58.1, 99.8, 12.6, 77.7, 32.1, 72.6, 58.1, 99.8, 12.6},
                       {25.7, 89.2, 12.4, 44.5, 32.1, 72.6, 58.1, 99.8, 12.6, 77.7},
                       {42.1, 37.2, 38.9, 23.7, 69.5, 49.7, 86.5, 47.1, 89.2, 23.5}};

float matrix2[tam][tam] ={{22.7, 41.2, 44.5, 33.3, 34.8, 32.1, 72.6, 58.1, 99.8, 12.6},
                       {18.6, 74.4, 76.3, 22.2, 65.3, 72.6, 58.1, 99.8, 12.6, 77.7},
                       {34.2, 77.5, 82.2, 43.3, 89.2, 52.1, 77.2, 28.9, 53.7, 99.5},
                       {15.7, 39.2, 22.4, 43.5, 37.1, 32.5, 25.9, 36.2, 45.2, 56.8},
                       {52.1, 77.2, 28.9, 53.7, 99.5, 72.6, 58.1, 99.8, 12.6, 77.7},
                       {22.7, 41.2, 44.5, 33.3, 34.8, 49.7, 86.5, 47.1, 89.2, 23.5},
                       {18.6, 74.4, 76.3, 22.2, 65.3, 25.7, 89.2, 12.4, 44.5, 32.1},
                       {34.2, 77.5, 82.2, 43.3, 89.2, 52.1, 77.2, 28.9, 53.7, 99.5},
                       {15.7, 39.2, 22.4, 43.5, 37.1, 34.2, 77.5, 82.2, 43.3, 89.2},
                       {52.1, 77.2, 28.9, 53.7, 99.5, 25.7, 89.2, 12.4, 44.5, 32.1}};

float result[tam][tam];

// Fun��o para multiplica��o de matrizes na forma matricial
void multiplyMatricial() {
    for(int i = 0; i < tam; i ++){
        for(int j = 0; j < tam; j ++){
            for(int k = 0; k < tam; k++){
                result[i][j] = result[i][j] + matrix1[i][k] * matrix2 [k][j];
            }
        }
    }
    cout<<"Multiplica��o Matricial"<<endl;
    for (int i = 0; i < tam; i++){
        cout << "|";
            for (int j = 0; j < tam; j++){
                cout << result[i][j] << "|";
            }
        cout << "\n";
    }
    cout<<endl;
}

// Fun��o para multiplica��o de matrizes por posi��o
void multiplyPosicional() {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            result[i][j] = matrix1[i][i] * matrix2[j][j];
        }
    }
    cout<<"Multiplica��o Posicional"<<endl;
    for (int i = 0; i < tam; i++){
        cout << "|";
            for (int j = 0; j < tam; j++){
                cout << result[i][j] << "|";
            }
        cout << "\n";
    }
    cout<<endl;
}

int main() {
    time1 = (double) clock();
    time1 = time1 / CLOCKS_PER_SEC;

    setlocale(LC_ALL, "Portuguese");

    multiplyMatricial();
    multiplyPosicional();

    timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
    printf("\nTempo executado: %f segundos\n", timedif);


    return 0;
}
