#include <iostream>
#include <vector>
#include <random>
using namespace std;

const int N = 15;
int dist[N][N];

int costoRuta(const vector<int>& ruta) {
    int c = 0;
    for (int i = 0; i + 1 < N; i++) c += dist[ruta[i]][ruta[i + 1]];
    c += dist[ruta[N - 1]][ruta[0]];
    return c;
}

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

        vector<bool> visitado2(N, false);
        vector<int> ruta2 = { inicio };
        visitado2[inicio] = true;

        for (int paso = 1; paso < N; paso++) {
            int masBarata = -1, mejorPos = -1;
            int menorAumento = 1000000;
            for (int c = 0; c < N; c++) {
                if (visitado2[c]) continue;
                for (int p = 0; p < (int)ruta2.size(); p++) {
                    int a = ruta2[p];
                    int b = ruta2[(p + 1) % ruta2.size()];
                    int aumento = dist[a][c] + dist[c][b] - dist[a][b];
                    if (aumento < menorAumento) {
                        menorAumento = aumento;
                        masBarata = c;
                        mejorPos = p + 1;
                    }
                }
            }
            ruta2.insert(ruta2.begin() + mejorPos, masBarata);   
            visitado2[masBarata] = true;
        }

        cout << "Inicio " << inicio << ":  NN = " << costoRuta(ruta)
            << "   Cheapest Insertion = " << costoRuta(ruta2) << endl;
    }
    return 0;
}