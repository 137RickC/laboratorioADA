#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Producto {

    string codigo;
    string nombre;
    float precio;
};

// =====================================================
// MERGESORT
// =====================================================

void merge(vector<Producto>& productos,
           int izq,
           int medio,
           int der) {

    vector<Producto> aux;

    int i = izq;
    int j = medio + 1;

    while (i <= medio && j <= der) {

        // Mayor precio primero

        if (productos[i].precio >= productos[j].precio) {

            aux.push_back(productos[i]);
            i++;

        } else {

            aux.push_back(productos[j]);
            j++;
        }
    }

    while (i <= medio) {

        aux.push_back(productos[i]);
        i++;
    }

    while (j <= der) {

        aux.push_back(productos[j]);
        j++;
    }

    for (int k = 0; k < aux.size(); k++) {

        productos[izq + k] = aux[k];
    }
}

void mergeSort(vector<Producto>& productos,
               int izq,
               int der) {

    if (izq < der) {

        int medio = izq + (der - izq) / 2;

        mergeSort(productos, izq, medio);

        mergeSort(productos, medio + 1, der);

        merge(productos, izq, medio, der);
    }
}

// =====================================================
// QUICKSORT
// =====================================================

int particion(vector<Producto>& productos,
              int low,
              int high) {

    float pivote = productos[high].precio;

    int i = low - 1;

    for (int j = low; j < high; j++) {

        // Mayor precio primero

        if (productos[j].precio > pivote) {

            i++;

            swap(productos[i], productos[j]);
        }
    }

    swap(productos[i + 1], productos[high]);

    return i + 1;
}

void quickSort(vector<Producto>& productos,
               int low,
               int high) {

    if (low < high) {

        int p = particion(productos, low, high);

        quickSort(productos, low, p - 1);

        quickSort(productos, p + 1, high);
    }
}

// =====================================================
// MOSTRAR
// =====================================================

void mostrar(const vector<Producto>& productos) {

    cout << left
         << setw(12) << "Codigo"
         << setw(30) << "Producto"
         << setw(12) << "Precio"
         << endl;

    for (const Producto& p : productos) {

        cout << left
             << setw(12) << p.codigo
             << setw(30) << p.nombre
             << fixed << setprecision(2)
             << p.precio
             << endl;
    }
}

// =====================================================
// MAIN
// =====================================================

int main() {

    ifstream archivo("productos.txt");

    if (!archivo.is_open()) {

        cout << "No se pudo abrir productos.txt\n";

        return 1;
    }

    vector<Producto> productos;

    string linea;

    while (getline(archivo, linea)) {

        stringstream ss(linea);

        Producto p;

        string precioTexto;

        getline(ss, p.codigo, ';');

        getline(ss, p.nombre, ';');

        getline(ss, precioTexto);

        p.precio = stof(precioTexto);

        productos.push_back(p);
    }

    archivo.close();

    vector<Producto> mergeProductos = productos;
    vector<Producto> quickProductos = productos;

    // Mergesort

    if (!mergeProductos.empty()) {

        mergeSort(
            mergeProductos,
            0,
            mergeProductos.size() - 1
        );
    }

    // Quicksort

    if (!quickProductos.empty()) {

        quickSort(
            quickProductos,
            0,
            quickProductos.size() - 1
        );
    }

    cout << "\n===== MERGESORT =====\n";

    mostrar(mergeProductos);

    cout << "\n===== QUICKSORT =====\n";

    mostrar(quickProductos);

    return 0;
}