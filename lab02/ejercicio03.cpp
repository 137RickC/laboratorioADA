#include <iostream>
#include <vector>
using namespace std;

void selectionSort(vector<float>& arr, int& comparaciones, int& intercambios) {
    int n = arr.size();

    comparaciones = 0;
    intercambios = 0;

    for (int i = 0; i < n - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < n; j++) {
            comparaciones++;

            if (arr[j] < arr[menor]) {
                menor = j;
            }
        }

        if (menor != i) {
            swap(arr[i], arr[menor]);
            intercambios++;
        }
    }
}

int main() {
    int n;
    cout << "Cantidad de numeros: ";
    cin >> n;
    vector<float> numeros(n);

    cout << "\nIngrese los numeros:\n";

    for (int i = 0; i < n; i++) {
        cout << "Numero " << i + 1 << ": ";
        cin >> numeros[i];
    }

    int comparaciones = 0;
    int intercambios = 0;

    selectionSort(numeros, comparaciones, intercambios);

    cout << "\nArreglo ordenado:\n";

    for (float numero : numeros) {
        cout << numero << " ";
    }

    cout << "\n\nComparaciones realizadas: " << comparaciones;
    cout << "\nIntercambios realizados: " << intercambios << endl;

    return 0;
}