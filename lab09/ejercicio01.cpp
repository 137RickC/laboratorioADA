#include <iostream>
#include <vector>
#include <random>
using namespace std;

const int N = 15; 
int dist[N][N];

int main() {
    mt19937 rng(42);
    uniform_int_distribution<int> d(10, 100);
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            dist[i][j] = dist[j][i] = d(rng);

    for (int inicio = 0; inicio < N; inicio++) {
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

        int costo = 0;
        for (int i = 0; i + 1 < N; i++) costo += dist[ruta[i]][ruta[i + 1]];
        costo += dist[ruta.back()][ruta[0]];

        cout << "Inicio " << inicio << ":\t";
        for (int c : ruta) cout << c << "\t -> ";
        cout << ruta[0] << "   Costo: " << costo << endl;
    }
    return 0;
}