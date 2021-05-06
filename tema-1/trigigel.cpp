#include <bits/stdc++.h>
using namespace std;

#define KMAX 4
#define MOD 1000000007

class Trigigel {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    long long n;

    void multiply_matrix(long long A[KMAX][KMAX], long long B[KMAX][KMAX],
                        long long C[KMAX][KMAX]) {
        long long tmp[KMAX][KMAX];

        for (int i = 0; i < KMAX; ++i) {
            for (int j = 0; j < KMAX; ++j) {
                long long sum = 0;

                for (int k = 0; k < KMAX; ++k) {
                    sum += 1LL * A[i][k] * B[k][j];
                }

                while (sum < 0) sum += MOD;
                tmp[i][j] = sum % MOD;
            }
        }

        //  C = tmp
        memcpy(C, tmp, sizeof(tmp));
    }

    void power_matrix(long long C[KMAX][KMAX], long long p,
                    long long R[KMAX][KMAX]) {
        long long tmp[KMAX][KMAX];

        for (int i = 0; i < KMAX; ++i) {
            for (int j = 0; j < KMAX; ++j) {
                tmp[i][j] = (i == j) ? 1 : 0;
            }
        }

        while (p != 1) {
            if  (p % 2 == 0) {
                multiply_matrix(C, C, C);
                p /= 2;
            } else {
                multiply_matrix(tmp, C, tmp);
                --p;
            }
        }

        multiply_matrix(C, tmp, R);
    }

    void read_input() {
        ifstream fin("trigigel.in");
        fin >> n;
        fin.close();
    }

    /* dp[i] = 2*dp[i - 1] - dp[i - 2] + dp[i - 3] - dp[i - 4]; */
    long long get_result() {
        // Cazuri initiale
        if (n == 1) return 1;
        if (n == 2) return 3;
        if (n == 3) return 6;
        if (n == 4) return 10;

        long long C[KMAX][KMAX] = { {0, 0, 0, -1},
                                    {1, 0, 0, 1},
                                    {0, 1, 0, -1},
                                    {0, 0, 1, 2} };

        power_matrix(C, n - 4, C);

        long long sol = 1 * C[0][3] + 3 * C[1][3] + 6 * C[2][3] + 10 * C[3][3];
        while (sol < 0) sol += MOD;
        return sol % MOD;
    }

    void print_output(long long result) {
        ofstream fout("trigigel.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto* trigigel = new Trigigel();

    trigigel->solve();
    delete trigigel;
    return 0;
}
