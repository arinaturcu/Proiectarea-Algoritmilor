#include <bits/stdc++.h>
using namespace std;

#define NMAX 1005

struct Graph {
    int n;
    int m;
    vector<int> adj[NMAX];
};

class Task {
    Graph *graph;
    int n, m, p;
    vector<vector<int>> questions;
    int visited[NMAX] = {0};
    vector<bool> ans;
    bool bad_sort;

 public:
    void solve() {
        read_input();
        get_result();
        print_output();
    }

 private:
    void read_input() {
        graph = new Graph;

        cin >> n >> m >> p;
        graph->n = n;
        graph->m = m;

        for (int i = 0, x, y; i < m; i++) {
            cin >> x >> y;
            graph->adj[x].push_back(y);
        }

        for (int i = 0; i < p; i++) {
            vector<int> v;

            for (int j = 0, x; j < n; j++) {
                cin >> x;
                v.push_back(x);
            }

            questions.push_back(v);
        }
    }

    void dfs(int node, int check[NMAX]) {
        visited[node] = 1;

        for (int i = 0; i < graph->adj[node].size(); i++) {
            if (visited[graph->adj[node][i]] == 0) {
                if (check[graph->adj[node][i]] == 1) bad_sort = true;

                dfs(graph->adj[node][i], check);
            }
        }

    }

    void get_result() {
        for (int i = 0; i < questions.size(); i++) {
            vector<int> list = questions[i];
            int check[NMAX] = { 0 };

            for (int j = 0; j < NMAX; j++) visited[j] = 0;

            bool ok = true;

            for (int j = 0; j < list.size(); j++) {
                check[list[j]] = 1;
                bad_sort = false;

                for (int j = 0; j < NMAX; j++) visited[j] = 0;

                dfs(list[j], check);

            }
            ans.push_back(!bad_sort);
        }   
    }

    void print_output() {
        for (int i = 0; i < ans.size(); i++) {
            if (ans[i]) {
                cout << "DA\n";
            } else 
                cout << "NU\n";
        }
    }
};

int main() {
  auto *task = new Task{};
  task->solve();
  delete task;
  return 0;
}