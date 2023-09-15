#include <iostream>
#include <vector>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <time.h>

double time1, timedif;
using namespace std;

// Estrutura para passar os argumentos da thread
struct ThreadArgs {
    vector<int>* arr;
    int start;
    int end;
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

    for (int i = args->start; i < args->end; i++) {
        for (int j = args->start; j < args->end - 1; j++) {
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

    int n = 2000;
    int num_threads = 2;

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

    vector<pthread_t> threads(num_threads);
    vector<ThreadArgs> thread_args(num_threads);

    // Divide o vetor em partes para cada thread
    int chunk_size = n / num_threads;
    int remainder = n % num_threads;

    int start = 0;
    for (int i = 0; i < num_threads; i++) {
        int end = start + chunk_size;
        if (i == num_threads - 1) {
            end += remainder;
        }
        thread_args[i].arr = &arr;
        thread_args[i].start = start;
        thread_args[i].end = end;
        start = end;

        pthread_create(&threads[i], NULL, bubbleSort, &thread_args[i]);
    }

    // Aguarda todas as threads terminarem
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Mescla os resultados das partes classificadas
    for (int i = 0; i < num_threads; i++) {
        for (int j = i + 1; j < num_threads; j++) {
            for (int k = thread_args[i].start; k < thread_args[i].end; k++) {
                for (int l = thread_args[j].start; l < thread_args[j].end; l++) {
                    if (arr[k] > arr[l]) {
                        swap(arr, k, l);
                    }
                }
            }
        }
    }
    timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
    printf("\nTempo executado: %f segundos\n", timedif);
    /*cout << "Vetor ordenado em ordem crescente:" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    */
    return 0;
}
