#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

const int INF = 1000000000;
// DIJKSTRA
void dijkstra(const vector<vector<pair<int, int>>>& grafo,int origen){
    int n = grafo.size();
    vector<int> distancia(n, INF);
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;
    distancia[origen] = 0;
    pq.push({0, origen});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > distancia[u])
            continue;
        for (auto [v, peso] : grafo[u]) {

            if (distancia[u] + peso < distancia[v]) {
                distancia[v] =
                    distancia[u] + peso;
                pq.push({
                    distancia[v],
                    v
                });
            }
        }
    }
}
// FLOYD WARSHALL
void floydWarshall(vector<vector<int>> dist){
    int n = dist.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF &&
                    dist[k][j] != INF &&
                    dist[i][k] + dist[k][j]
                    < dist[i][j]) {

                    dist[i][j] =
                        dist[i][k]
                        + dist[k][j];
                }
            }
        }
    }
}
// GENERAR GRAFO
void generarGrafo(int n,vector<vector<pair<int, int>>>& grafo,
    vector<vector<int>>& matriz){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int>
        peso(1, 100);
    uniform_int_distribution<int>
        probabilidad(1, 100);
    grafo.assign(n, {});
    matriz.assign(
        n,
        vector<int>(n, INF)
    );

    for (int i = 0; i < n; i++)
        matriz[i][i] = 0;

    // Conectar cada vértice con el siguiente
    // para asegurar un grafo conectado.

    for (int i = 0; i < n - 1; i++) {
        int p = peso(gen);
        grafo[i].push_back({i + 1, p});
        grafo[i + 1].push_back({i, p});

        matriz[i][i + 1] = p;
        matriz[i + 1][i] = p;
    }
    // Generar conexiones adicionales
    for (int i = 0; i < n; i++) {
        for (int j = i + 2; j < n; j++) {
            if (probabilidad(gen) <= 5) {
                int p = peso(gen);

                grafo[i].push_back({j, p});
                grafo[j].push_back({i, p});

                matriz[i][j] = p;
                matriz[j][i] = p;
            }
        }
    }
}

int main() {
    int tamanos[] = {
        10,
        100,
        500
    };

    for (int n : tamanos) {
        vector<vector<pair<int, int>>> grafo;
        vector<vector<int>> matriz;

        generarGrafo( n, grafo, matriz );
        // Dijkstra
        auto inicioD = high_resolution_clock::now();
        dijkstra(grafo, 0);

        auto finD = high_resolution_clock::now();

        double tiempoD = duration<double, milli>(finD - inicioD).count();
        
        // Floyd
        auto inicioF = high_resolution_clock::now();

        floydWarshall(matriz);

        auto finF = high_resolution_clock::now();

        double tiempoF = duration<double, milli>(finF - inicioF).count();
        cout << "\nVertices: " << n << endl;

        cout << "Dijkstra: " << tiempoD << " ms" << endl;

        cout << "Floyd-Warshall: " << tiempoF << " ms" << endl;

        cout << "------------------------\n";
    }

    return 0;
}