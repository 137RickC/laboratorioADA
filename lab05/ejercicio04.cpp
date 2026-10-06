#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

struct Arista {
    int u, v, peso;
};

vector<int> padre, rango;

int encontrar(int x) {
    if (padre[x] != x)
        padre[x] = encontrar(padre[x]);

    return padre[x];
}

bool unir(int x, int y) {
    int rx = encontrar(x);
    int ry = encontrar(y);

    if (rx == ry)
        return false;

    if (rango[rx] < rango[ry])
        swap(rx, ry);

    padre[ry] = rx;

    if (rango[rx] == rango[ry])
        rango[rx]++;

    return true;
}

// KRUSKAL
int kruskal(int n, vector<Arista> aristas) {
    sort(aristas.begin(), aristas.end(),
        [](Arista a, Arista b) {
            return a.peso < b.peso;
        });

    padre.resize(n);
    rango.assign(n, 0);

    for (int i = 0; i < n; i++)
        padre[i] = i;

    int pesoTotal = 0;
    int cantidad = 0;

    for (auto& a : aristas) {

        if (unir(a.u, a.v)) {

            pesoTotal += a.peso;
            cantidad++;

            if (cantidad == n - 1)
                break;
        }
    }

    return pesoTotal;
}

// PRIM
int prim(int n, vector<Arista> aristas) {

    vector<vector<pair<int, int>>> grafo(n);

    for (auto& a : aristas) {

        grafo[a.u].push_back({a.v, a.peso});
        grafo[a.v].push_back({a.u, a.peso});
    }

    vector<bool> enArbol(n, false);

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    pq.push({0, 0});

    int pesoTotal = 0;

    while (!pq.empty()) {

        auto [peso, u] = pq.top();
        pq.pop();

        if (enArbol[u])
            continue;

        enArbol[u] = true;

        pesoTotal += peso;

        for (auto [v, p] : grafo[u]) {

            if (!enArbol[v])
                pq.push({p, v});
        }
    }

    return pesoTotal;
}

// Generar grafo conexo
vector<Arista> generarGrafo(int n, bool denso) {
    vector<Arista> aristas;
    // Primero conectamos todos los vertices
    // para asegurar que el grafo sea conexo
    for (int i = 0; i < n - 1; i++) {

        Arista a;

        a.u = i;
        a.v = i + 1;
        a.peso = 1 + rand() % 100;

        aristas.push_back(a);
    }

    // Agregar conexiones adicionales
    for (int i = 0; i < n; i++) {

        for (int j = i + 2; j < n; j++) {

            int numero = rand() % 100;

            // Grafo denso: 60%
            if (denso && numero < 60) {

                Arista a;

                a.u = i;
                a.v = j;
                a.peso = 1 + rand() % 100;

                aristas.push_back(a);
            }

            // Grafo disperso: 5%
            if (!denso && numero < 5) {

                Arista a;

                a.u = i;
                a.v = j;
                a.peso = 1 + rand() % 100;

                aristas.push_back(a);
            }
        }
    }

    return aristas;
}

int main() {
    srand(time(NULL));
    int tamanios[] = {50, 100, 200};

    for (int t = 0; t < 3; t++) {
        int n = tamanios[t];
        for (int tipo = 0; tipo < 2; tipo++) {
            bool denso;

            if (tipo == 0)
                denso = false;
            else
                denso = true;

            vector<Arista> aristas =
                generarGrafo(n, denso);


            cout << "\nVertices: " << n << endl;
            cout << "Aristas: " << aristas.size() << endl;

            if (denso)
                cout << "Tipo: Denso" << endl;
            else
                cout << "Tipo: Disperso" << endl;

            // KRUSKAL

            auto inicioK =
                chrono::high_resolution_clock::now();

            int pesoK =
                kruskal(n, aristas);

            auto finK =
                chrono::high_resolution_clock::now();

            auto tiempoK =
                chrono::duration_cast<
                    chrono::microseconds
                >(finK - inicioK).count();

            // PRIM
            auto inicioP =
                chrono::high_resolution_clock::now();

            int pesoP =
                prim(n, aristas);

            auto finP =
                chrono::high_resolution_clock::now();

            auto tiempoP =
                chrono::duration_cast<
                    chrono::microseconds
                >(finP - inicioP).count();

            cout << "Kruskal: "
                << tiempoK
                << " microsegundos"
                << endl;

            cout << "Prim: "
                << tiempoP
                << " microsegundos"
                << endl;

            cout << "Peso Kruskal: "
                << pesoK << endl;

            cout << "Peso Prim: "
                << pesoP << endl;
        }
    }

    return 0;
}