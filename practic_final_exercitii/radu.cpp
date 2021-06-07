#include <bits/stdc++.h>
using namespace std;

#define NMAX 1005

class Task {
    int grid[NMAX][NMAX];
    int n, m, d;
    int i1, j1, i2, j2;
    int dist1[NMAX][NMAX];
    int dist2[NMAX][NMAX];
    unordered_map<int, int> map1;
    unordered_map<int, int> map2;

 public:
  void solve() {
    read_input();
    print_output(get_result());
  }

 private:

  void read_input() {
    cin >> n >> m >> d;
    cin >> i1 >> j1 >> i2 >> j2;
    for (int i = 1; i <= n; i++) {
        for (int j = 1, x; j <= m; j++) {
            cin >> x;
            grid[i][j] = x;
        }
    }  
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dist1[i][j] = INT_MAX;
            dist2[i][j] = INT_MAX;
        }
    }    
  }

vector<pair<int, int>> get_adj(int x, int y) {
    vector<pair<int, int>> adj;
    adj.push_back(pair<int, int> (x + 1, y));
    adj.push_back(pair<int, int> (x - 1, y));
    adj.push_back(pair<int, int> (x, y - 1));
    adj.push_back(pair<int, int> (x, y + 1));
    return adj;
  }

  bool is_pos_outside(pair<int, int> pos) {
    int x = pos.first;
    int y = pos.second;
    if (x > n || y > m || x < 1 || y < 1) {
      return true;
    }
    return false;
  }

    void bfs (int x, int y, int dist[NMAX][NMAX]) {
        queue<pair<int, int>> q;
        q.push(pair<int, int>(x, y));
        dist[x][y] = 0;

        while (!q.empty()) {
            pair<int, int> pos = q.front();
            q.pop();

            vector<pair<int, int>> adj = get_adj(pos.first, pos.second);
            for (int i = 0; i < adj.size(); i++) {
                pair<int, int> next_pos = adj[i];
                if (is_pos_outside(next_pos)) {
                    continue;
                }
                if (dist[pos.first][pos.second] + 1 < dist[next_pos.first][next_pos.second]) {
                    dist[next_pos.first][next_pos.second] = dist[pos.first][pos.second] + 1;
                    q.push(next_pos);
                }
            }
        }
    }

  int get_result() {
    bfs(i1, j1, dist1);
    bfs(i2, j2, dist2);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (map1.find(dist1[i][j]) == map1.end() || map1.find(dist1[i][j])->second < grid[i][j]) {
                map1.insert(pair<int, int> (dist1[i][j], grid[i][j]));
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (map2.find(dist2[i][j]) == map2.end() || map2.find(dist2[i][j])->second < grid[i][j]) {
                map2.insert(pair<int, int> (dist2[i][j], grid[i][j]));
            }
        }
    }

    int ans = INT_MIN;
    for (int d1 = 0; d1 <= d; d1++) {
        for (int d2 = 0; d2 + d1 <= d; d2++) {
            int total = map1.find(d1)->second + map2.find(d2)->second;
            if (total > ans) {
                ans = total;
            }
        }
    }
    
    return ans;
  }

  void print_output(int ans) {
      cout << ans << endl;
  }
};

int main() {
  auto *task = new Task{};
  task->solve();
  delete task;
  return 0;
}