#include <iostream>
#include <string>
#include <vector>
#include <algorithm>   // sort(), binary_search()
#include <sstream>     // para separar el texto en palabras
using namespace std;

int buscarEnTexto(const string &texto, const string &palabra, int &comparaciones) {
    comparaciones = 0;
    int apariciones = 0;
    int n = texto.size();
    int m = palabra.size();

    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m) {
            comparaciones++;
            if (texto[i + j] != palabra[j]) break;
            j++;
        }
        if (j == m) apariciones++;   // coincidencia completa
    }
    return apariciones;
}
// Metodo 2: Búsqueda binaria en una lista ORDENADA de palabras
bool buscarEnListaOrdenada(vector<string> lista, const string &palabra, int &comparaciones) {
    sort(lista.begin(), lista.end());   // primero se ordena
    comparaciones = 0;
    int inicio = 0, fin = lista.size() - 1;

    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;
        comparaciones++;
        if (lista[medio] == palabra) return true;
        else if (lista[medio] < palabra) inicio = medio + 1;
        else fin = medio - 1;
    }
    return false;
}

int main() {
    string texto = "el perro corre y el gato duerme y el perro ladra";
    string palabra = "perro";

    // Metodo 1: buscar la palabra dentro del texto completo
    int comp1;
    int veces = buscarEnTexto(texto, palabra, comp1);
    cout << "Busqueda en texto:\n";
    cout << "  La palabra \"" << palabra << "\" aparece " << veces << " veces.\n";
    cout << "  Comparaciones realizadas: " << comp1 << "\n\n";
    //Metodo 2: separar el texto en palabras y buscar en la lista 
    vector<string> listaPalabras;
    stringstream ss(texto);
    string p;
    while (ss >> p) listaPalabras.push_back(p);

    int comp2;
    bool encontrado = buscarEnListaOrdenada(listaPalabras, palabra, comp2);
    cout << "Busqueda binaria en lista ordenada:\n";
    cout << "  La palabra \"" << palabra << "\" "
         << (encontrado ? "SI existe" : "NO existe") << " en la lista.\n";
    cout << "  Comparaciones realizadas: " << comp2 << "\n";

    return 0;
}