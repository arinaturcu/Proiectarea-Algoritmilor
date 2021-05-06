#include <bits/stdc++.h>
using namespace std;

class Trigigel {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    unsigned long long n;

    void read_input() {
        ifstream fin("trigigel.in");
        fin >> n;
        fin.close();
    }

    long long get_result() {
        long long *dp = (long long*)malloc(sizeof(long long) * n);

        if (dp == NULL) {
            cout << "nu e memorie\n";
            exit(1);
        }

        cout << n << endl;

        dp[0] = 1;
        for (int i = 1; i < n; ++i) {
            if (i <= 3) {
                dp[i] = i + 1 + dp[i - 1];
                continue;
            }

            dp[i] = (i + 1 + dp[i - 1]) % 1000000007;

            for (int j = (i - 1) % 3; j <= i - 4; j = j + 3) {
                dp[i] = (dp[i] + dp[j]) % 1000000007;
            }

            // dp[i] = 2*dp[i - 1] - dp[i - 2] + dp[i - 3] - dp[i - 4];
            // dp[i] = 3 + dp[i - 1] + dp[i - 3];
        }

        for (int i = 0; i < n; ++i) {
            cout << dp[i] << " ";
        }

        cout << endl;

        return dp[n - 1];

        // long long result_for_now = 1;

        // long long digit_count[3] = {0};

        // digit_count[0] = 1;
        // cout << 1 << " ";

        // for (int i = 1; i < 4; ++i) {
        //     result_for_now = i + 1 + digit_count[(i - 1) % 3];

        //     digit_count[i % 3] += result_for_now % 1000000007;
        //     cout << result_for_now << " ";
        // }

        // for (int i = 4; i < n; ++i) {
        //     result_for_now = (i % 1000000007 + 1 + digit_count[(i - 1) % 3])
        // % 1000000007;
        //     digit_count[i % 3] = (digit_count[i % 3] +
        // result_for_now % 1000000007) % 1000000007;

        //     cout << result_for_now << " ";
        // }

        // cout << endl;

        // return result_for_now % 1000000007;
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
