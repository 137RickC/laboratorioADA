#include <iostream>
#include <vector>
using namespace std;

void selectionSort(vector<float>& arreglo,
                   long long& comparaciones,
                   long long& intercambios) {

    int n = arreglo.size();
    comparaciones = 0;
    intercambios = 0;

    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {

            comparaciones++;

            if (arreglo[j] < arreglo[menor]) {
                menor = j;
            }
        }

        if (menor != i) {
            swap(arreglo[i], arreglo[menor]);
            intercambios++;
        }
    }
}

int main() {
    int n;
    cout << "Cantidad de numeros: ";
    cin >> n;
    vector<float> numeros(n);

    for (int i = 0; i < n; i++) {
        cout << "Numero " << i + 1 << ": ";
        cin >> numeros[i];
    }

    long long comparaciones;
    long long intercambios;

    selectionSort(
        numeros,
        comparaciones,
        intercambios
    );

    cout << "\nArreglo ordenado:\n";

    for (float numero : numeros) {
        cout << numero << " ";
    }

    cout << "\n\nComparaciones: "
         << comparaciones;

    cout << "\nIntercambios: "
         << intercambios << endl;

    return 0;
}