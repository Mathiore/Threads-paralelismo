#include <iostream>
#include <vector>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <time.h>

using namespace std;

double time1, timedif;
// Estrutura para passar os argumentos da thread
struct ThreadArgs {
    vector<int>* arr;
};

// Função para trocar dois elementos em um vetor
void swap(vector<int>& arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Função executada por cada thread
void* bubbleSort(void* arg) {
    ThreadArgs* args = static_cast<ThreadArgs*>(arg);
    vector<int>& arr = *(args->arr);
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr, j, j + 1);
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    time1 = (double) clock();
    time1 = time1 / CLOCKS_PER_SEC;
    setlocale(LC_ALL, "Portuguese");

    int n = 20000;

    vector<int> arr(n);

    // Preenche o vetor com números aleatórios em ordem decrescente
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }

    // Embaralha os elementos do vetor
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(arr, i, j);
    }

    pthread_t thread;
    ThreadArgs args;
    args.arr = &arr;

    pthread_create(&thread, NULL, bubbleSort, &args);

    pthread_join(thread, NULL);

    /*cout << "Vetor ordenado em ordem crescente:" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;*/
    timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
    printf("\nTempo executado: %f segundos\n", timedif);

    return 0;
}
