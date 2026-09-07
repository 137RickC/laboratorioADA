#include <iostream>
using namespace std;

int busquedaSecuencial(int arr[], int n, int clave) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == clave)
            return i; // encontrado
    }
    return -1; // no encontrado
}

int main() {
    int datos[] = { 2, 4, 6, 8, 10 };
    int n = 5;
    int clave = 8;

    int pos = busquedaSecuencial(datos, n, clave);
    if (pos != -1)
        cout << "Elemento encontrado en la posicion " << pos << endl;
    else
        cout << "Elemento no encontrado" << endl;

    return 0;
}
