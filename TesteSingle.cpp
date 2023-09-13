#include <iostream>
#include <pthread.h>
#include <locale.h>
#include <time.h>
#include <cstdlib>

using namespace std;

double time1, timedif;
const int N = 15; // Tamanho da matriz

// Função para alocar e preencher uma matriz com números aleatórios entre 1 e 100
float** criarMatrizAleatoria() {
    float** matriz = new float*[N];
    for (int i = 0; i < N; ++i) {
        matriz[i] = new float[N];
        for (int j = 0; j < N; ++j) {
            matriz[i][j] = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 99.0)) + 1.0;
        }
    }
    return matriz;
}

// Função para liberar a memória alocada para a matriz
void liberarMatriz(float** matriz) {
    for (int i = 0; i < N; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

// Função para multiplicação de matrizes na forma matricial
void* multiplyMatricesMatricial(void* arg) {
    float** matrix1 = criarMatrizAleatoria();
    float** matrix2 = criarMatrizAleatoria();

    float** result = new float*[N];
    for (int i = 0; i < N; ++i) {
        result[i] = new float[N];
    }

    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j ++) {
            for (int k = 0; k < N; k++) {
                result[i][j] = result[i][j] + matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    cout << "Multiplicação Matricial" << endl;
    for (int i = 0; i < N; i++) {
        cout << "|";
        for (int j = 0; j < N; j++) {
            cout << result[i][j] << "|";
        }
        cout << "\n";
    }
    cout << endl;

    liberarMatriz(matrix1);
    liberarMatriz(matrix2);
    liberarMatriz(result);

    pthread_exit(NULL);
}

// Função para multiplicação de matrizes por posição
void* multiplyMatricesPositional(void* arg) {
    float** matrix1 = criarMatrizAleatoria();
    float** matrix2 = criarMatrizAleatoria();

    float** result = new float*[N];
    for (int i = 0; i < N; ++i) {
        result[i] = new float[N];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = matrix1[i][i] * matrix2[j][j];
        }
    }

    cout << "Multiplicação Posicional" << endl;
    for (int i = 0; i < N; i++) {
        cout << "|";
        for (int j = 0; j < N; j++) {
            cout << result[i][j] << "|";
        }
        cout << "\n";
    }
    cout << endl;

    liberarMatriz(matrix1);
    liberarMatriz(matrix2);
    liberarMatriz(result);

    pthread_exit(NULL);
}

int main() {
    srand(static_cast<unsigned>(time(NULL))); // Inicialize a semente para números aleatórios

    time1 = (double) clock();
    time1 = time1 / CLOCKS_PER_SEC;

    setlocale(LC_ALL, "Portuguese");

    pthread_t t1;
    int a1 = 1;
    pthread_create(&t1, NULL, multiplyMatricesMatricial, (void*)(&a1)); // Cria thread
    pthread_join(t1, NULL);

    pthread_create(&t1, NULL, multiplyMatricesPositional, (void*)(&a1)); // Cria thread
    pthread_join(t1, NULL);

    timedif = (((double) clock()) / CLOCKS_PER_SEC) - time1;
    printf("\nTempo executado: %f segundos\n", timedif);

    return 0;
}
