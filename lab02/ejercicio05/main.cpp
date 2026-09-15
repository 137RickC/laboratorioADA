#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

struct Videojuego {
    string codigo;
    string titulo;
    double puntaje;
};
struct Estadisticas {
    long long comparaciones = 0;
    long long intercambios = 0;
    double tiempo = 0;
};
//CARGAR ARCHIVO
vector<Videojuego> cargarArchivo(const string& nombreArchivo) {
    vector<Videojuego> juegos;

    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo.\n";
        return juegos;
    }

    string linea;

    while (getline(archivo, linea)) {

        stringstream ss(linea);

        string codigo;
        string titulo;
        string puntajeTexto;

        getline(ss, codigo, ';');
        getline(ss, titulo, ';');
        getline(ss, puntajeTexto);

        Videojuego juego;

        juego.codigo = codigo;
        juego.titulo = titulo;
        juego.puntaje = stod(puntajeTexto);

        juegos.push_back(juego);
    }

    archivo.close();

    return juegos;
}
// INSERTION SORT Mayor a menor
Estadisticas insertionSort(vector<Videojuego>& juegos) {
    Estadisticas estadisticas;

    auto inicio = high_resolution_clock::now();

    int n = juegos.size();

    for (int i = 1; i < n; i++) {

        int j = i;

        while (j > 0) {

            estadisticas.comparaciones++;

            if (juegos[j - 1].puntaje < juegos[j].puntaje) {

                swap(juegos[j - 1], juegos[j]);

                estadisticas.intercambios++;

                j--;

            } else {

                break;
            }
        }
    }

    auto fin = high_resolution_clock::now();

    estadisticas.tiempo =
        duration<double, micro>(
            fin - inicio
        ).count();

    return estadisticas;
}

// SELECTION SORTMayor a menor
Estadisticas selectionSort(vector<Videojuego>& juegos) {

    Estadisticas estadisticas;

    auto inicio = high_resolution_clock::now();

    int n = juegos.size();

    for (int i = 0; i < n - 1; i++) {

        int mayor = i;

        for (int j = i + 1; j < n; j++) {

            estadisticas.comparaciones++;

            if (juegos[j].puntaje >
                juegos[mayor].puntaje) {

                mayor = j;
            }
        }

        if (mayor != i) {

            swap(juegos[i], juegos[mayor]);

            estadisticas.intercambios++;
        }
    }

    auto fin = high_resolution_clock::now();

    estadisticas.tiempo =
        duration<double, micro>(
            fin - inicio
        ).count();

    return estadisticas;
}

void mostrar(const vector<Videojuego>& juegos) {

    cout << left
         << setw(10) << "Codigo"
         << setw(30) << "Titulo"
         << setw(10) << "Puntaje"
         << endl;

    cout << string(50, '-') << endl;

    for (const Videojuego& juego : juegos) {

        cout << left
             << setw(10) << juego.codigo
             << setw(30) << juego.titulo
             << setw(10) << juego.puntaje
             << endl;
    }
}

void exportarCSV(
    const vector<Videojuego>& juegos,
    const string& nombreArchivo
) {

    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {

        cout << "Error al crear CSV.\n";
        return;
    }

    archivo << "Codigo,Titulo,Puntaje\n";

    for (const Videojuego& juego : juegos) {

        archivo
            << juego.codigo << ","
            << "\"" << juego.titulo << "\"" << ","
            << juego.puntaje
            << "\n";
    }

    archivo.close();

    cout << "Archivo creado: "
         << nombreArchivo
         << endl;
}

int main() {

    vector<Videojuego> videojuegos =
        cargarArchivo("videojuegos.txt");

    if (videojuegos.empty()) {

        cout << "No existen datos.\n";
        return 0;
    }

    cout << "\nDATOS ORIGINALES\n";

    mostrar(videojuegos);


    // Crear copias para que ambos algoritmos
    // trabajen con exactamente los mismos datos.

    vector<Videojuego> juegosInsertion =
        videojuegos;

    vector<Videojuego> juegosSelection =
        videojuegos;

    // INSERTION SORT

    Estadisticas estInsertion =
        insertionSort(juegosInsertion);

    cout << "\nINSERTION SORT\n";

    mostrar(juegosInsertion);

    cout << "\nComparaciones: "
         << estInsertion.comparaciones
         << endl;

    cout << "Intercambios: "
         << estInsertion.intercambios
         << endl;

    cout << "Tiempo: "
         << estInsertion.tiempo
         << " microsegundos\n";

    // SELECTION SORT
    Estadisticas estSelection =
        selectionSort(juegosSelection);

    cout << "\nSELECTION SORT\n";

    mostrar(juegosSelection);

    cout << "\nComparaciones: "
         << estSelection.comparaciones
         << endl;

    cout << "Intercambios: "
         << estSelection.intercambios
         << endl;

    cout << "Tiempo: "
         << estSelection.tiempo
         << " microsegundos\n";

    // EXPORTACION
    exportarCSV(
        juegosInsertion,
        "videojuegos_insertion.csv"
    );
    exportarCSV(
        juegosSelection,
        "videojuegos_selection.csv"
    );

    return 0;
}