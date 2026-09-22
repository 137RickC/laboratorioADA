#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

// ---------------- MERGESORT ----------------

void merge(vector<int>& arr, int izq, int medio, int der) {

    vector<int> aux;

    int i = izq;
    int j = medio + 1;

    while (i <= medio && j <= der) {

        if (arr[i] <= arr[j]) {
            aux.push_back(arr[i]);
            i++;
        } else {
            aux.push_back(arr[j]);
            j++;
        }
    }

    while (i <= medio) {
        aux.push_back(arr[i]);
        i++;
    }

    while (j <= der) {
        aux.push_back(arr[j]);
        j++;
    }

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

// ---------------- BUSQUEDA BINARIA ----------------

int busquedaBinaria(const vector<int>& arr, int buscado) {

    int izq = 0;
    int der = arr.size() - 1;

    while (izq <= der) {

        int medio = izq + (der - izq) / 2;

        if (arr[medio] == buscado)
            return medio;

        if (arr[medio] < buscado)
            izq = medio + 1;
        else
            der = medio - 1;
    }

    return -1;
}

// ---------------- BUSQUEDA SECUENCIAL ----------------

int busquedaSecuencial(const vector<int>& arr, int buscado) {

    for (int i = 0; i < arr.size(); i++) {

        if (arr[i] == buscado)
            return i;
    }

    return -1;
}

int main() {

    int n;
    int buscado;

    cout << "Cantidad de elementos: ";
    cin >> n;

    vector<int> original(n);

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dist(1, 100000);

    for (int& x : original) {
        x = dist(gen);
    }

    cout << "Numero a buscar: ";
    cin >> buscado;

    // ---------------- SECUENCIAL ----------------

    auto inicioSec = high_resolution_clock::now();

    int posSec = busquedaSecuencial(original, buscado);

    auto finSec = high_resolution_clock::now();

    // ---------------- ORDENAMIENTO ----------------

    vector<int> ordenado = original;

    auto inicioOrd = high_resolution_clock::now();

    mergeSort(ordenado, 0, ordenado.size() - 1);

    auto finOrd = high_resolution_clock::now();

    // ---------------- BINARIA ----------------

    auto inicioBin = high_resolution_clock::now();

    int posBin = busquedaBinaria(ordenado, buscado);

    auto finBin = high_resolution_clock::now();

    auto tiempoSec =
        duration_cast<nanoseconds>(finSec - inicioSec).count();

    auto tiempoOrd =
        duration_cast<nanoseconds>(finOrd - inicioOrd).count();

    auto tiempoBin =
        duration_cast<nanoseconds>(finBin - inicioBin).count();

    cout << "\nRESULTADOS\n";

    cout << "Busqueda secuencial: "
         << tiempoSec << " ns\n";

    cout << "Ordenamiento Mergesort: "
         << tiempoOrd << " ns\n";

    cout << "Busqueda binaria: "
         << tiempoBin << " ns\n";

    cout << "Tiempo ordenamiento + busqueda binaria: "
         << tiempoOrd + tiempoBin << " ns\n";

    cout << "\nComplejidades teoricas:\n";

    cout << "Busqueda secuencial: O(n)\n";

    cout << "Mergesort: O(n log n)\n";

    cout << "Busqueda binaria: O(log n)\n";

    cout << "Total: O(n log n + log n) = O(n log n)\n";

    return 0;
}