#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

//Metodo 1: Suma con bucle
long sumaConBucle(long n, long &pasos) {
    long suma = 0;
    pasos = 0;
    for (long i = 1; i <= n; i++) {
        suma += i;
        pasos++;    // se ejecuta n veces -> O(n)
    }
    return suma;
}

// Método 2: Suma con formula directa de Gauss
long sumaConFormula(long n, int &pasos) {
    pasos = 1;      // una sola operacion, sin importar el valor de n -> O(1)
    return n * (n + 1) / 2;
}

int main() {
    long n;
    cout << "Ingrese el valor de n: ";
    cin >> n;

    // Metodo 1
    long pasos1;
    auto inicio1 = high_resolution_clock::now();
    long resultado1 = sumaConBucle(n, pasos1);
    auto fin1 = high_resolution_clock::now();
    auto duracion1 = duration_cast<nanoseconds>(fin1 - inicio1);

    // Método 2 
    int pasos2;
    auto inicio2 = high_resolution_clock::now();
    long resultado2 = sumaConFormula(n, pasos2);
    auto fin2 = high_resolution_clock::now();
    auto duracion2 = duration_cast<nanoseconds>(fin2 - inicio2);

    cout << "\n=== RESULTADOS ===\n";
    cout << "Suma con bucle   = " << resultado1
         << " | pasos = " << pasos1
         << " | tiempo = " << duracion1.count() << " ns  --> O(n)\n";

    cout << "Suma con formula = " << resultado2
         << " | pasos = " << pasos2
         << " | tiempo = " << duracion2.count() << " ns  --> O(1)\n";

    return 0;
}