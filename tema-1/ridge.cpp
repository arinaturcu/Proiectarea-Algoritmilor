#include <bits/stdc++.h>
using namespace std;

struct mountain {
    int height;
    int cost;
};

class Ridge {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    vector<mountain> mountains;

    void read_input() {
        ifstream fin("ridge.in");

        fin >> n;

        for (int i = 0; i < n; i++) {
            mountain m;
            fin >> m.height >> m.cost;
            mountains.push_back(m);
        }

        fin.close();
    }

    long long get_result() {
        /* i will never cut more than 2 blocks 
        from a mountain => j = {0, 1, 2} */
        long long **dp = (long long **) malloc(sizeof(long long*) * n);
        for (int i = 0; i < n; ++i) {
            dp[i] = (long long *) malloc(sizeof(long long) * 3);
        }

        /* initialize the first line */
        for (int j = 0; j < 3; ++j) {
            dp[0][j] = mountains[0].cost * j;
        }

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < 3; ++j) {
                long long min_old_cost = LONG_LONG_MAX;

                /* gigel can't dig underground */
                if (mountains[i].height - j < 0) {
                    dp[i][j] = LONG_LONG_MAX;
                    continue;
                }

                /* find minimum preivious cost and add to the current cost */
                for (int k = 0; k < 3; ++k) {
                    if (mountains[i].height - j != mountains[i - 1].height-k) {
                        if (dp[i - 1][k] < min_old_cost) {
                            min_old_cost = dp[i - 1][k];
                        }
                    }
                }

                dp[i][j] = j * mountains[i].cost + min_old_cost;
            }
        }

        long long min_total_cost = LONG_LONG_MAX;

        /* find minimum cost considering all mountains -> dp[n - 1] */
        for (int i = 0; i < 3; ++i) {
            if (dp[n - 1][i] < min_total_cost)
                min_total_cost = dp[n - 1][i];
        }

        return min_total_cost;
    }

    void print_output(long long result) {
        ofstream fout("ridge.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto* ridge = new Ridge();

    ridge->solve();
    delete ridge;
    return 0;
}
