#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Recursivo ingenuo:
long long fibRecursivo(int n) {
    if (n <= 1) return n;
    return fibRecursivo(n - 1) + fibRecursivo(n - 2);
}

// Memorizacion
long long fibMemo(int n, vector<long long>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);
    return memo[n];
}

// Tabulacion 
long long fibTabla(int n) {
    if (n <= 1) return n;
    vector<long long> F(n + 1);
    F[0] = 0;
    F[1] = 1;
    for (int i = 2; i <= n; i++)
        F[i] = F[i - 1] + F[i - 2];
    return F[n];
}

int main() {
    int valores[] = { 10, 20, 30 };

    for (int n : valores) {
        auto t1 = high_resolution_clock::now();
        long long r1 = fibRecursivo(n);
        auto t2 = high_resolution_clock::now();

        vector<long long> memo(n + 1, -1);
        long long r2 = fibMemo(n, memo);
        auto t3 = high_resolution_clock::now();

        long long r3 = fibTabla(n);
        auto t4 = high_resolution_clock::now();

        cout << "n = " << n << endl;
        cout << "  Recursivo:    " << r1 << "  tiempo: " << duration_cast<nanoseconds>(t2 - t1).count() << " ns" << endl;
        cout << "  Memorizacion: " << r2 << "  tiempo: " << duration_cast<nanoseconds>(t3 - t2).count() << " ns" << endl;
        cout << "  Tabulacion:   " << r3 << "  tiempo: " << duration_cast<nanoseconds>(t4 - t3).count() << " ns" << endl;
    }

    return 0;
}
