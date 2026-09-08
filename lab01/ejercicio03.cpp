#include <iostream>
#include <string>
#include <vector>
#include <algorithm>   // sort()
#include <chrono>
using namespace std;
using namespace std::chrono;

void insertionSort(vector<string> &lista, long &comparaciones) {
    comparaciones = 0;
    int n = lista.size();

    for (int i = 1; i < n; i++) {
        string actual = lista[i];
        int j = i - 1;

        while (j >= 0) {
            comparaciones++;
            if (lista[j] > actual) {
                lista[j + 1] = lista[j];
                j--;
            } else {
                break;
            }
        }
        lista[j + 1] = actual;
    }
}

int main() {
    vector<string> nombres1 = {"Carlos", "Ana", "Zoe", "Luis", "Beatriz", "David", "Mario"};
    vector<string> nombres2 = nombres1;   // copia idéntica para comparar de forma justa

    //Método 1: Insertion Sort propio
    long comparaciones;
    auto inicio1 = high_resolution_clock::now();
    insertionSort(nombres1, comparaciones);
    auto fin1 = high_resolution_clock::now();
    auto duracion1 = duration_cast<nanoseconds>(fin1 - inicio1);

    //Metodo 2: sort() de la biblioteca estándar
    auto inicio2 = high_resolution_clock::now();
    sort(nombres2.begin(), nombres2.end());
    auto fin2 = high_resolution_clock::now();
    auto duracion2 = duration_cast<nanoseconds>(fin2 - inicio2);

    cout << "=== Insertion Sort (propio) ===\n";
    cout << "Resultado: ";
    for (auto &nombre : nombres1) cout << nombre << " ";
    cout << "\nComparaciones: " << comparaciones
         << " | Tiempo: " << duracion1.count() << " ns\n\n";

    cout << "=== std::sort() ===\n";
    cout << "Resultado: ";
    for (auto &nombre : nombres2) cout << nombre << " ";
    cout << "\nTiempo: " << duracion2.count() << " ns\n";
    cout << "(std::sort no expone el numero de comparaciones directamente,\n";
    cout << " pero internamente usa Introsort: O(n log n) en el peor caso)\n";

    return 0;
}