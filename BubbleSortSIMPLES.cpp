#include <iostream>
#include <ctime>
#include <cstdlib>
#include <time.h>

using namespace std;

double time1, timedif;

void bubbleSort(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Trocar os elementos arr[j] e arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        // Se nenhum elemento foi trocado durante a passagem interna, o vetor está ordenado
        if (!swapped) {
            break;
        }
    }
}

int main() {
    time1 = (double) clock();
    time1 = time1 / CLOCKS_PER_SEC;
    setlocale(LC_ALL, "Portuguese");
    // Configurar a semente do gerador de números aleatórios com o tempo atual
    srand(time(0));

    int n = 20000;

    // Criar um vetor com elementos em ordem decrescente
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }

    /*cout << "Vetor gerado aleatoriamente em ordem decrescente:" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
    */
    // Aplicar Bubble Sort para ordenar o vetor em ordem crescente
    bubbleSort(arr, n);
    timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
    /*cout << "Vetor ordenado em ordem crescente:" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    */
    printf("\nTempo executado: %f segundos\n", timedif);
    return 0;
}
