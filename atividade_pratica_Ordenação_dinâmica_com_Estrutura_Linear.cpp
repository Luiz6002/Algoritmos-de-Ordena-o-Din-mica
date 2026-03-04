#include <stdio.h>
#include <stdlib.h>

long comparacoes = 0;
long trocas = 0;

void resetarContadores() {
    comparacoes = 0;
    trocas = 0;
}

void imprimirVetor(int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

/* ================= BUBBLE SORT ================= */
void bubbleSort(int v[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (v[j] > v[j + 1]) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                trocas++;
            }
        }
    }
}

/* ================= SELECTION SORT ================= */
void selectionSort(int v[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j] < v[min])
                min = j;
        }
        if (min != i) {
            temp = v[i];
            v[i] = v[min];
            v[min] = temp;
            trocas++;
        }
    }
}

/* ================= INSERTION SORT ================= */
void insertionSort(int v[], int n) {
    int i, j, chave;
    for (i = 1; i < n; i++) {
        chave = v[i];
        j = i - 1;

        while (j >= 0 && v[j] > chave) {
            comparacoes++;
            v[j + 1] = v[j];
            trocas++;
            j--;
        }
        if (j >= 0)
            comparacoes++;

        v[j + 1] = chave;
    }
}

/* ================= QUICK SORT ================= */
int particionar(int v[], int low, int high) {
    int pivo = v[high];
    int i = low - 1;
    int j, temp;

    for (j = low; j < high; j++) {
        comparacoes++;
        if (v[j] < pivo) {
            i++;
            temp = v[i];
            v[i] = v[j];
            v[j] = temp;
            trocas++;
        }
    }

    temp = v[i + 1];
    v[i + 1] = v[high];
    v[high] = temp;
    trocas++;

    return i + 1;
}

void quickSort(int v[], int low, int high) {
    int pi;
    if (low < high) {
        pi = particionar(v, low, high);
        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}

/* ================= MERGE SORT ================= */
void merge(int v[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int*) malloc(n1 * sizeof(int));
    int *R = (int*) malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = v[l + i];
    for (j = 0; j < n2; j++)
        R[j] = v[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        comparacoes++;
        if (L[i] <= R[j])
            v[k++] = L[i++];
        else
            v[k++] = R[j++];
        trocas++;
    }

    while (i < n1) {
        v[k++] = L[i++];
        trocas++;
    }

    while (j < n2) {
        v[k++] = R[j++];
        trocas++;
    }

    free(L);
    free(R);
}

void mergeSort(int v[], int l, int r) {
    int m;
    if (l < r) {
        m = (l + r) / 2;
        mergeSort(v, l, m);
        mergeSort(v, m + 1, r);
        merge(v, l, m, r);
    }
}

/* ================= SHELL SORT ================= */
void shellSort(int v[], int n) {
    int gap, i, j, temp;

    for (gap = n / 2; gap > 0; gap = gap / 2) {
        for (i = gap; i < n; i++) {
            temp = v[i];
            j = i;

            while (j >= gap && v[j - gap] > temp) {
                comparacoes++;
                v[j] = v[j - gap];
                trocas++;
                j = j - gap;
            }
            if (j >= gap)
                comparacoes++;

            v[j] = temp;
        }
    }
}

/* ================= HEAP SORT ================= */
void heapify(int v[], int n, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;
    int temp;

    if (esq < n) {
        comparacoes++;
        if (v[esq] > v[maior])
            maior = esq;
    }

    if (dir < n) {
        comparacoes++;
        if (v[dir] > v[maior])
            maior = dir;
    }

    if (maior != i) {
        temp = v[i];
        v[i] = v[maior];
        v[maior] = temp;
        trocas++;
        heapify(v, n, maior);
    }
}

void heapSort(int v[], int n) {
    int i, temp;

    for (i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);

    for (i = n - 1; i > 0; i--) {
        temp = v[0];
        v[0] = v[i];
        v[i] = temp;
        trocas++;
        heapify(v, i, 0);
    }
}

/* ================= MAIN ================= */
int main() {

    int opcao, qtd, valor;
    int *vetor = NULL;
    int tamanho = 0;
    int i;

    printf("Escolha o algoritmo:\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Selection Sort\n");
    printf("3 - Insertion Sort\n");
    printf("4 - Quick Sort\n");
    printf("5 - Merge Sort\n");
    printf("6 - Shell Sort\n");
    printf("7 - Heap Sort\n");

    printf("\nOpcao: ");
    scanf("%d", &opcao);

    printf("Quantos valores deseja inserir? ");
    scanf("%d", &qtd);

    for (i = 0; i < qtd; i++) {

        printf("\nDigite o valor: ");
        scanf("%d", &valor);

        tamanho++;
        vetor = (int*) realloc(vetor, tamanho * sizeof(int));
        vetor[tamanho - 1] = valor;

        resetarContadores();

        switch(opcao) {
            case 1: bubbleSort(vetor, tamanho); break;
            case 2: selectionSort(vetor, tamanho); break;
            case 3: insertionSort(vetor, tamanho); break;
            case 4: quickSort(vetor, 0, tamanho - 1); break;
            case 5: mergeSort(vetor, 0, tamanho - 1); break;
            case 6: shellSort(vetor, tamanho); break;
            case 7: heapSort(vetor, tamanho); break;
            default: printf("Opcao invalida!\n");
        }

        printf("Estrutura atual: ");
        imprimirVetor(vetor, tamanho);

        printf("Comparacoes: %ld\n", comparacoes);
        printf("Trocas: %ld\n", trocas);
    }

    free(vetor);
    return 0;
}
