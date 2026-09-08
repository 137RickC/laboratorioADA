#include <iostream>
#include <chrono>   // Para medir tiempo de ejecución
using namespace std;
using namespace std::chrono;

// Se basa en la propiedad: mcd(a, b) = mcd(b, a % b)
int mcdEuclides(int a, int b, int &divisiones) {
    divisiones = 0;
    while (b != 0) {
        int resto = a % b;
        a = b;
        b = resto;
        divisiones++;   // contamos cuántas divisiones hace
    }
    return a;
}

// Va restando el menor al mayor hasta que ambos sean iguales
int mcdBucleResta(int a, int b, long &pasos) {
    pasos = 0;
    while (a != b) {
        if (a > b) {
            a = a - b;
        } else {
            b = b - a;
        }
        pasos++;    // contamos cuántas restas hace
    }
    return a;
}

int main() {
    int a, b;
    cout << "Ingrese dos numeros enteros positivos: ";
    cin >> a >> b;

    //Medimos el método de Euclides 
    int divisiones;
    auto inicio1 = high_resolution_clock::now();
    int resultado1 = mcdEuclides(a, b, divisiones);
    auto fin1 = high_resolution_clock::now();
    auto duracion1 = duration_cast<nanoseconds>(fin1 - inicio1);

    //Medimos el método con bucle de restas 
    long pasos;
    auto inicio2 = high_resolution_clock::now();
    int resultado2 = mcdBucleResta(a, b, pasos);
    auto fin2 = high_resolution_clock::now();
    auto duracion2 = duration_cast<nanoseconds>(fin2 - inicio2);

    cout << "\n=== RESULTADOS ===\n";
    cout << "MCD (Euclides)   = " << resultado1
         << " | divisiones realizadas = " << divisiones
         << " | tiempo = " << duracion1.count() << " ns\n";

    cout << "MCD (Bucle resta) = " << resultado2
         << " | restas realizadas = " << pasos
         << " | tiempo = " << duracion2.count() << " ns\n";

    return 0;
}