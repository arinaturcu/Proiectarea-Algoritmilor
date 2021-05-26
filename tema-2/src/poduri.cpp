#include <bits/stdc++.h>
using namespace std;

class Poduri {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    static constexpr int NMAX = 2050;

    int n, m;  // grid size
    int x, y;  // initial position
    char **grid;

    void read_input() {
        ifstream fin("poduri.in");

        fin >> n >> m;
        fin >> x >> y;

        // alloc memory for grid and read
        grid = new char*[n + 1];
        for (int i = 1; i <= n; i++) {
            grid[i] = new char[m + 1];

            for (int j = 1; j <= m; ++j) {
                fin >> grid[i][j];
            }
        }

        fin.close();
    }

    vector<pair<int, int>> get_neighs(pair<int, int> cell, char dir) {
        vector<pair<int, int>> neighs;

        if (dir == 'V') {
            neighs.push_back(pair<int, int> (cell.first - 1, cell.second));
            neighs.push_back(pair<int, int> (cell.first + 1, cell.second));

            return neighs;
        }

        if (dir == 'O') {
            neighs.push_back(pair<int, int> (cell.first, cell.second - 1));
            neighs.push_back(pair<int, int> (cell.first, cell.second + 1));

            return neighs;
        }

        return neighs;
    }

    int get_result() {
        // initialize distance matrix with +oo
        int **d = new int*[n + 1];
        for (int i = 1; i <= n; ++i) {
            d[i] = new int[m + 1];

            for (int j = 1; j <= m; ++j) {
                d[i][j] = INT_MAX;
            }
        }

        vector<pair<int, int>> neighs;
        vector<pair<int, int>> to_add;

        pair<int, int> src;
        src.first  = x;
        src.second = y;

        queue<pair<int, int>> q;
        q.push(src);

        d[x][y] = 0;

        while (!q.empty()) {
            pair<int, int> pos = q.front();
            q.pop();

            switch (grid[pos.first][pos.second]) {
                case 'V':
                case 'O':
                    neighs = get_neighs(pos, grid[pos.first][pos.second]);
                    break;

                case 'D':
                    neighs = get_neighs(pos, 'V');
                    to_add = get_neighs(pos, 'O');
                    neighs.insert(neighs.end(), to_add.begin(), to_add.end());
                    break;

                default:
                    break;
            }

            for (auto neigh : neighs) {
                if (neigh.first <= 0 || neigh.first > n ||
                    neigh.second <= 0 || neigh.second > m) {
                    return d[pos.first][pos.second] + 1;
                }

                if (d[neigh.first][neigh.second] <=
                    d[pos.first][pos.second] + 1) {
                    continue;
                }

                d[neigh.first][neigh.second] = d[pos.first][pos.second] + 1;
                q.push(neigh);
            }
        }

        return -1;
    }

    void print_output(int result) {
        ofstream fout("poduri.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto* poduri = new (nothrow)Poduri();

    if (!poduri) {
        cerr << "new failed\n";
        return -1;
    }

    poduri->solve();
    delete poduri;
    return 0;
}
