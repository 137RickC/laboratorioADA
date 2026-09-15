#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;

void insertionSort(vector<double>& arreglo) {
    int n = arreglo.size();

    for (int i = 1; i < n; i++) {
        double actual = arreglo[i];
        int j = i - 1;

        while (j >= 0 && arreglo[j] > actual) {

            arreglo[j + 1] = arreglo[j];
            j--;
        }
        arreglo[j + 1] = actual;
    }
}

void selectionSort(vector<double>& arreglo) {
    int n = arreglo.size();
    for (int i = 0; i < n - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < n; j++) {

            if (arreglo[j] < arreglo[menor]) {
                menor = j;
            }
        }
        if (menor != i) {
            swap(arreglo[i], arreglo[menor]);
        }
    }
}

void ordenar(vector<double>& arreglo, const string& tipo) {
    if (tipo == "insertion") {
        insertionSort(arreglo);
    } else if (tipo == "selection") {
        selectionSort(arreglo);

    } else {
        cout << "Metodo de ordenamiento no valido.\n";
    }
}

vector<double> generarAleatorios(int n) {
    vector<double> datos(n);
    random_device rd;
    mt19937 generador(rd());

    uniform_real_distribution<double> distribucion(
        0.0,
        10000.0
    );
    for (int i = 0; i < n; i++) {
        datos[i] = distribucion(generador);
    }
    return datos;
}

void evaluar(int n) {
    vector<double> original = generarAleatorios(n);

    vector<double> datosInsertion = original;
    vector<double> datosSelection = original;
    // Insertion Sort
    auto inicio1 = high_resolution_clock::now();

    ordenar(datosInsertion, "insertion");

    auto fin1 = high_resolution_clock::now();

    double tiempoInsertion =
        duration<double, milli>(
            fin1 - inicio1
        ).count();

    // Selection Sort
    auto inicio2 = high_resolution_clock::now();

    ordenar(datosSelection, "selection");

    auto fin2 = high_resolution_clock::now();

    double tiempoSelection =
        duration<double, milli>(
            fin2 - inicio2
        ).count();

    cout << "\nCantidad: " << n << endl;

    cout << "Insertion Sort: "
         << tiempoInsertion
         << " ms\n";

    cout << "Selection Sort: "
         << tiempoSelection
         << " ms\n";
}

int main() {

    evaluar(1000);
    evaluar(5000);
    evaluar(10000);

    return 0;
}