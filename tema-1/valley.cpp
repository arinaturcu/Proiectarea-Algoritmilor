#include <bits/stdc++.h>
using namespace std;

class Valley {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    vector<long long> heights;

    void read_input() {
        ifstream fin("valley.in");
        fin >> n;

        for (int i = 0, x; i < n; i++) {
            fin >> x;
            heights.push_back(x);
        }

        fin.close();
    }

    long long get_result() {
        long long bottom = LONG_LONG_MAX;
        int bottom_index = -1;
        long long count = 0;

        for (int i = 0; i < n; ++i) {
            if (heights[i] < bottom) {
                bottom = heights[i];
                bottom_index = i;
            }
        }

        if (n == 3) {
            if (bottom_index == 0) {
                return heights[1] - heights[0];
            } else if (bottom_index == 2) {
                return heights[1] - heights[2];
            }
        }

        if (bottom_index == 0)  {
            count += heights[1] - bottom;
            heights[1] = bottom;
        } else if (bottom_index == n - 1) {
            count += heights[n - 2] - bottom;
            heights[n - 2] = bottom;
        }

        for (int i = 1; i < bottom_index; ++i) {
            if (heights[i] > heights[i - 1]) {
                count += (heights[i] - heights[i - 1]);
                heights[i] = heights[i - 1];
            }
        }

        for (int i = n - 1;  i > bottom_index; --i) {
            if (heights[i - 1] > heights[i]) {
                count += heights[i - 1] - heights[i];
                heights[i - 1] = heights[i];
            }
        }

        return count;
    }

    void print_output(long long result) {
        ofstream fout("valley.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto* valley = new Valley();

    valley->solve();
    delete valley;
    return 0;
}
