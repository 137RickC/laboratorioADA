#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 1000000000;

int main() {
    int n = 6;

    string nombre[] = {
        "A", "B", "C", "D", "E", "F"
    };

    vector<vector<int>> dist(n, vector<int>(n, INF));
    vector<vector<int>> siguiente(n, vector<int>(n, -1));

    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        siguiente[i][i] = i;
    }

    auto agregarArista =
        [&](int u, int v, int peso) {

        dist[u][v] = peso;
        dist[v][u] = peso;

        siguiente[u][v] = v;
        siguiente[v][u] = u;
    };

    agregarArista(0, 1, 4);
    agregarArista(0, 2, 2);
    agregarArista(1, 2, 1);
    agregarArista(1, 3, 5);
    agregarArista(2, 3, 8);
    agregarArista(2, 4, 10);
    agregarArista(3, 4, 2);
    agregarArista(3, 5, 6);
    agregarArista(4, 5, 3);

    // Floyd-Warshall
    for (int k = 0; k < n; k++) {

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                if (dist[i][k] != INF &&
                    dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {

                    dist[i][j] =
                        dist[i][k] + dist[k][j];

                    siguiente[i][j] =
                        siguiente[i][k];
                }
            }
        }
    }

    cout << "Matriz de distancias minimas:\n\n";
    cout << "\t";

    for (int i = 0; i < n; i++)
        cout << nombre[i] << "\t";
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << nombre[i] << "\t";
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }

        cout << endl;
    }

    int origen, destino;

    cout << "\nOrigen (0=A, 1=B, 2=C, 3=D, 4=E, 5=F): ";
    cin >> origen;

    cout << "Destino: ";
    cin >> destino;

    if (siguiente[origen][destino] == -1) {

        cout << "No existe camino." << endl;
        return 0;
    }

    vector<int> camino;

    int actual = origen;

    camino.push_back(actual);

    while (actual != destino) {

        actual = siguiente[actual][destino];
        camino.push_back(actual);
    }

    cout << "\nDistancia minima: "
         << dist[origen][destino] << endl;

    cout << "Camino: ";

    for (int i = 0; i < camino.size(); i++) {

        cout << nombre[camino[i]];

        if (i < camino.size() - 1)
            cout << " -> ";
    }
    cout << endl;

    return 0;
}