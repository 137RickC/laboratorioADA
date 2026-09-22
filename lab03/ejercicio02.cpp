#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;
// PIVOTE FIJO 
int particionFija(vector<float>& arr, int low, int high) {
    float pivote = arr[high];
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

void quickSortFijo(vector<float>& arr, int low, int high) {
    if (low < high) {
        int p = particionFija(arr, low, high);

        quickSortFijo(arr, low, p - 1);
        quickSortFijo(arr, p + 1, high);
    }
}

//PIVOTE ALEATORIO
int particionAleatoria(vector<float>& arr, int low, int high, mt19937& gen) {
    uniform_int_distribution<int> dist(low, high);

    int indicePivote = dist(gen);

    swap(arr[indicePivote], arr[high]);

    return particionFija(arr, low, high);
}
void quickSortAleatorio(vector<float>& arr,
                        int low,
                        int high,
                        mt19937& gen) {

    if (low < high) {
        int p = particionAleatoria(arr, low, high, gen);

        quickSortAleatorio(arr, low, p - 1, gen);
        quickSortAleatorio(arr, p + 1, high, gen);
    }
}
int main() {
    int n;

    cout << "Cantidad de numeros: ";
    cin >> n;

    vector<float> original(n);

    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<float> dist(0.0, 10000.0);

    for (int i = 0; i < n; i++) {
        original[i] = dist(gen);
    }

    vector<float> fijo = original;
    vector<float> aleatorio = original;

    // Pivote fijo

    auto inicio1 = high_resolution_clock::now();

    quickSortFijo(fijo, 0, fijo.size() - 1);

    auto fin1 = high_resolution_clock::now();

    // Pivote aleatorio

    auto inicio2 = high_resolution_clock::now();

    quickSortAleatorio(
        aleatorio,
        0,
        aleatorio.size() - 1,
        gen
    );

    auto fin2 = high_resolution_clock::now();

    auto tiempoFijo =
        duration_cast<microseconds>(fin1 - inicio1).count();

    auto tiempoAleatorio =
        duration_cast<microseconds>(fin2 - inicio2).count();

    cout << "\nRESULTADOS\n";

    cout << "Pivote fijo: "
         << tiempoFijo
         << " microsegundos\n";
    cout << "Pivote fijo: ";
    for (float x : fijo) {
        cout << x << " ";
    }
    for(int n : fijo){
        cout << n << " ";
    }

    cout << "Pivote aleatorio: "
         << tiempoAleatorio
         << " microsegundos\n";
    for(int n : aleatorio){
        cout << n << " ";
    }
    return 0;
}