#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 10;
int dist[N][N];                        

// CAMBIO: lugares reales de Arequipa con coordenadas aproximadas
string nombre[N] = { "UNSA", "Plaza de Armas", "Santa Catalina", "Museo Santuarios Andinos",
                    "Mercado San Camilo", "Mirador de Yanahuara", "Mirador de Carmen Alto",
                    "Molino de Sabandia", "Mansion del Fundador", "Mall Porongoche" };
double lat[N] = { -16.4047, -16.3989, -16.3955, -16.4004, -16.4021,
                -16.3876, -16.3703, -16.4573, -16.4436, -16.4175 };
double lon[N] = { -71.5248, -71.5369, -71.5366, -71.5374, -71.5339,
                -71.5418, -71.5432, -71.4951, -71.5641, -71.5149 };

int costoRuta(const vector<int>& ruta) {
    int c = 0;
    for (int i = 0; i + 1 < N; i++) c += dist[ruta[i]][ruta[i + 1]];
    c += dist[ruta[N - 1]][ruta[0]];
    return c;
}

int main() {

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            double r = M_PI / 180;
            double h = pow(sin((lat[j] - lat[i]) * r / 2), 2) +
                       cos(lat[i] * r) * cos(lat[j] * r) * pow(sin((lon[j] - lon[i]) * r / 2), 2);
            dist[i][j] = (int)(2 * 6371000 * asin(sqrt(h)));
        }

    int inicio = 0;
    vector<bool> visitado(N, false);
    vector<int> ruta = { inicio };
    visitado[inicio] = true;
    for (int paso = 1; paso < N; paso++) {
        int actual = ruta.back();
        int masCercano = -1;
        int mejorDist = 1000000;
        for (int c = 0; c < N; c++) {
            if (!visitado[c] && dist[actual][c] < mejorDist) {
                mejorDist = dist[actual][c];
                masCercano = c;
            }
        }
        ruta.push_back(masCercano);
        visitado[masCercano] = true;
    }
    cout << "Nearest Neighbor: " << costoRuta(ruta) << " m" << endl;

    bool mejora = true;
    while (mejora) {
        mejora = false;
        for (int i = 1; i < N - 1; i++) {
            for (int j = i + 1; j < N; j++) {
                vector<int> nueva = ruta;
                reverse(nueva.begin() + i, nueva.begin() + j + 1);
                if (costoRuta(nueva) < costoRuta(ruta)) {
                    ruta = nueva;
                    mejora = true;
                }
            }
        }
    }

    cout << "NN + 2-opt: " << costoRuta(ruta) << " m" << endl << "Ruta: ";
    for (int c : ruta) cout << nombre[c] << " -> ";
    cout << nombre[ruta[0]] << endl;

    vector<int> ciudades = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int mejorCosto = 1000000000;
    do {
        int costo = dist[0][ciudades[0]];
        for (int i = 0; i < (int)ciudades.size() - 1; i++)
            costo += dist[ciudades[i]][ciudades[i + 1]];
        costo += dist[ciudades.back()][0];
        mejorCosto = min(mejorCosto, costo);
    } while (next_permutation(ciudades.begin(), ciudades.end()));
    cout << "Optimo (fuerza bruta): " << mejorCosto << " m" << endl;
    return 0;
}