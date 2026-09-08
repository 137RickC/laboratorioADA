#include <iostream>
#include <string>
using namespace std;

// Metodo: comparación con dos punteros (izquierda / derecha)
// Convertimos el número a cadena para comparar dígito por dígito
bool esPalindromo(long numero, int &comparaciones) {
    string s = to_string(numero);
    comparaciones = 0;

    int izquierda = 0;
    int derecha = s.size() - 1;

    while (izquierda < derecha) {
        comparaciones++;
        if (s[izquierda] != s[derecha]) {
            return false;   // apenas encuentra una diferencia, termina (mejor caso)
        }
        izquierda++;
        derecha--;
    }
    return true;   // si nunca hubo diferencias, es palindromo (peor caso: recorre todo)
}

int main() {
    long numero;
    cout << "Ingrese un numero entero: ";
    cin >> numero;

    int comparaciones;
    bool resultado = esPalindromo(numero, comparaciones);

    cout << "\nEl numero " << numero << (resultado ? " SI" : " NO")
         << " es palindromo.\n";
    cout << "Comparaciones realizadas: " << comparaciones << "\n";
    cout << "Numero de digitos (d): " << to_string(numero).size() << "\n";
    cout << "En el peor caso se hacen como maximo d/2 comparaciones (O(d)).\n";

    return 0;
}