#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

// =====================================================
// MERGESORT
// =====================================================

void merge(vector<int>& arr, int izq, int medio, int der) {

    vector<int> aux;

    int i = izq;
    int j = medio + 1;

    while (i <= medio && j <= der) {

        if (arr[i] <= arr[j]) {
            aux.push_back(arr[i++]);
        } else {
            aux.push_back(arr[j++]);
        }
    }

    while (i <= medio)
        aux.push_back(arr[i++]);

    while (j <= der)
        aux.push_back(arr[j++]);

    for (int k = 0; k < aux.size(); k++) {
        arr[izq + k] = aux[k];
    }
}

void mergeSort(vector<int>& arr, int izq, int der) {

    if (izq < der) {

        int medio = izq + (der - izq) / 2;

        mergeSort(arr, izq, medio);
        mergeSort(arr, medio + 1, der);

        merge(arr, izq, medio, der);
    }
}

// =====================================================
// QUICKSORT
// =====================================================

int particion(vector<int>& arr, int low, int high) {

    int pivote = arr[high];

    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (arr[j] < pivote) {

            i++;

            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {

    if (low < high) {

        int p = particion(arr, low, high);

        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

// =====================================================
// INSERTION SORT
// =====================================================

void insertionSort(vector<int>& arr) {

    for (int i = 1; i < arr.size(); i++) {

        int actual = arr[i];

        int j = i - 1;

        while (j >= 0 && arr[j] > actual) {

            arr[j + 1] = arr[j];

            j--;
        }

        arr[j + 1] = actual;
    }
}

// =====================================================
// SELECTION SORT
// =====================================================

void selectionSort(vector<int>& arr) {

    for (int i = 0; i < arr.size() - 1; i++) {

        int menor = i;

        for (int j = i + 1; j < arr.size(); j++) {

            if (arr[j] < arr[menor]) {
                menor = j;
            }
        }

        swap(arr[i], arr[menor]);
    }
}

// =====================================================
// MAIN
// =====================================================

int main() {

    const int n = 10000;

    vector<int> datos(n);

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dist(1, 100000);

    for (int& x : datos) {
        x = dist(gen);
    }

    // Todos reciben exactamente los mismos datos

    vector<int> mergeDatos = datos;
    vector<int> quickDatos = datos;
    vector<int> insertionDatos = datos;
    vector<int> selectionDatos = datos;

    // ---------------- MERGESORT ----------------

    auto inicio = high_resolution_clock::now();

    mergeSort(
        mergeDatos,
        0,
        mergeDatos.size() - 1
    );

    auto fin = high_resolution_clock::now();

    cout << "Mergesort: "
         << duration_cast<microseconds>(fin - inicio).count()
         << " microsegundos\n";

    // ---------------- QUICKSORT ----------------

    inicio = high_resolution_clock::now();

    quickSort(
        quickDatos,
        0,
        quickDatos.size() - 1
    );

    fin = high_resolution_clock::now();

    cout << "Quicksort: "
         << duration_cast<microseconds>(fin - inicio).count()
         << " microsegundos\n";

    // ---------------- INSERTION ----------------

    inicio = high_resolution_clock::now();

    insertionSort(insertionDatos);

    fin = high_resolution_clock::now();

    cout << "Insertion Sort: "
         << duration_cast<microseconds>(fin - inicio).count()
         << " microsegundos\n";

    // ---------------- SELECTION ----------------

    inicio = high_resolution_clock::now();

    selectionSort(selectionDatos);

    fin = high_resolution_clock::now();

    cout << "Selection Sort: "
         << duration_cast<microseconds>(fin - inicio).count()
         << " microsegundos\n";

    return 0;
}