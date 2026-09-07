#include <iostream>
using namespace std;

int busquedaBinaria(int arr[], int n, int clave) {
    int inicio = 0, fin = n - 1;
    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;
        if (arr[medio] == clave) {
            return medio;
        } else if (arr[medio] < clave) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }
    return -1;
}

int main() {
    int datos[] = { 2, 4, 6, 8, 10, 12, 14 };
    int n = 7;
    int clave = 10;
    int pos = busquedaBinaria(datos, n, clave);

    if (pos != -1)
        cout << "Elemento encontrado en la posicion " << pos << endl;
    else
        cout << "Elemento no encontrado" << endl;

    return 0;
}
