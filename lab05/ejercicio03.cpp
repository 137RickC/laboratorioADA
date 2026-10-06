#include <iostream>
#include <vector>
#include <algorithm>
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

int main() {
    int n = 6;
    vector<Arista> aristas = {
        {0, 1, 4},
        {0, 2, 2},
        {1, 2, 1},
        {1, 3, 5},
        {2, 3, 8},
        {2, 4, 10},
        {3, 4, 2},
        {3, 5, 6},
        {4, 5, 3}
    };

    string nombres[] = {
        "A", "B", "C", "D", "E", "F"
    };

    padre.resize(n);
    rango.assign(n, 0);

    for (int i = 0; i < n; i++)
        padre[i] = i;

    int componentes = n;
    int pesoTotal = 0;
    int ronda = 1;

    while (componentes > 1) {
        vector<int> barata(n, -1);
        // Buscar la arista mas barata
        // para cada componente
        for (int i = 0; i < aristas.size(); i++) {

            int u = encontrar(aristas[i].u);
            int v = encontrar(aristas[i].v);

            if (u == v)
                continue;

            if (barata[u] == -1 ||
                aristas[i].peso < aristas[barata[u]].peso) {

                barata[u] = i;
            }

            if (barata[v] == -1 ||
                aristas[i].peso < aristas[barata[v]].peso) {

                barata[v] = i;
            }
        }

        cout << "\n RONDA " << ronda << endl;

        bool agregado = false;

        for (int i = 0; i < n; i++) {
            if (barata[i] == -1)
                continue;

            Arista a = aristas[barata[i]];

            int u = encontrar(a.u);
            int v = encontrar(a.v);

            if (u == v)
                continue;

            if (unir(a.u, a.v)) {
                cout << nombres[a.u]
                    << " - "
                    << nombres[a.v]
                    << " (peso "
                    << a.peso
                    << ")"
                    << endl;

                pesoTotal += a.peso;
                componentes--;
                agregado = true;
            }
        }

        cout << "Componentes restantes: "
            << componentes << endl;

        if (!agregado) {
            cout << "El grafo no es conexo." << endl;
            return 0;
        }
        ronda++;
    }

    cout << "\nPeso total del MST: "
        << pesoTotal << endl;

    cout << "Peso obtenido por Kruskal y Prim: 13" << endl;

    if (pesoTotal == 13)
        cout << "Los resultados coinciden." << endl;

    return 0;
}