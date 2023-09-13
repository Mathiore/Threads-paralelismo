#include <iostream>
#include <pthread.h>
#include <locale.h>
#include <time.h>

using namespace std;

double time1, timedif;

// declarando as matrizes utilizadas
float matrix1[5][5] = {{32.5, 25.9, 36.2, 45.2, 56.8},
                       {49.7, 86.5, 47.1, 89.2, 23.5},
                       {72.6, 58.1, 99.8, 12.6, 77.7},
                       {25.7, 89.2, 12.4, 44.5, 32.1},
                       {42.1, 37.2, 38.9, 23.7, 69.5}};

float matrix2[5][5] = {{22.7, 41.2, 44.5, 33.3, 34.8},
                       {18.6, 74.4, 76.3, 22.2, 65.3},
                       {34.2, 77.5, 82.2, 43.3, 89.2},
                       {15.7, 39.2, 22.4, 43.5, 37.1},
                       {52.1, 77.2, 28.9, 53.7, 99.5}};

float result[5][5];

float result2[5][5];

// Função para multiplicação de matrizes na forma matricial
void* multiplyMatricesMatricial(void* arg) {
    for(int i = 0; i < 5; i ++){
        for(int j = 0; j < 5; j ++){
            for(int k = 0; k < 5; k++){
                result[i][j] = result[i][j] + matrix1[i][k] * matrix2 [k][j];
            }
        }
    }
    pthread_exit(NULL);
}

// Função para multiplicação de matrizes por posição
void* multiplyMatricesPositional(void* arg) {

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            result2[i][j] = matrix1[i][i] * matrix2[j][j];
        }
    }
    pthread_exit(NULL);
}

int main() {
    time1 = (double) clock();
    time1 = time1 / CLOCKS_PER_SEC;

    setlocale(LC_ALL, "Portuguese");

    pthread_t t1, t2;
    int a1 = 1, a2 = 2;
    pthread_create(&t1, NULL, multiplyMatricesMatricial, (void *)(&a1));; //cria thread
    pthread_create(&t2, NULL, multiplyMatricesPositional, (void *)(&a2));; //cria thread

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    cout<<"Multiplicação Matricial"<<endl;
    for (int i = 0; i < 5; i++){
        cout << "|";
            for (int j = 0; j < 5; j++){
                cout << result[i][j] << "|";
            }
        cout << "\n";
    }

    cout<<endl;
    cout<<"Multiplicação Posicional"<<endl;
    for (int i = 0; i < 5; i++){
        cout << "|";
            for (int j = 0; j < 5; j++){
                cout << result2[i][j] << "|";
            }
        cout << "\n";
    }
    cout<<endl;


    timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
    printf("\nTempo executado: %f segundos\n", timedif);

    return 0;
}
