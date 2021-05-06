#include <bits/stdc++.h>
using namespace std;

struct stock {
    int current_value;
    int min_value;
    int max_value;
};

class Stocks {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, b, l;
    vector<stock> stocks;

    void read_input() {
        ifstream fin("stocks.in");
        fin >> n >> b >> l;

        for (int i = 0, d; i < n; i++) {
            stock a;
            fin >> a.current_value >> a.min_value >> a.max_value;
            stocks.push_back(a);
        }

        fin.close();
    }

    int get_result() {
        /* Put 3D array on heap */
        int ***dp = (int***) malloc(sizeof(int**) * (n + 1));
        for (int i = 0; i <= n; ++i) {
            dp[i] = (int**) malloc(sizeof(int*) * (b + 1));
            for (int j = 0; j <= b; ++j) {
                dp[i][j] = (int*) malloc(sizeof(int) * (l + 1));
            }
        }

        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= b; ++j) {
                for (int k = 0; k <= l; ++k) {
                    if (i == 0 || j == 0 || k == 0) {
                        dp[i][j][k] = 0;
                        continue;
                    }

                    if (stocks[i - 1].current_value <= j
                        && (stocks[i - 1].current_value
                          - stocks[i - 1].min_value) <= k) {
                        int stock_added =
                            (stocks[i - 1].max_value -
                             stocks[i - 1].current_value)
                            + dp[i - 1]
                                [j - stocks[i - 1].current_value]
                                [k - (stocks[i - 1].current_value
                                    - stocks[i - 1].min_value)];

                        int stock_not_added = dp[i - 1][j][k];

                        if (stock_added > stock_not_added) {
                            dp[i][j][k] = stock_added;
                        } else {
                            dp[i][j][k] = stock_not_added;
                        }
                    } else {
                        dp[i][j][k] = dp[i - 1][j][k];
                    }
                }
            }
        }

        return dp[n][b][l];
    }

    void print_output(int result) {
        ofstream fout("stocks.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto* stocks = new Stocks();

    stocks->solve();
    delete stocks;
    return 0;
}
