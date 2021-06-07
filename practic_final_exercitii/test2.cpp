#include <bits/stdc++.h>
using namespace std;

class Graph {
	int N;
	vector<int>* adj;

 public:
    Graph(int N) {
	    this->N = N;
	    adj = new vector<int>[N + 1];
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void isTopologicalSort(vector<int> to_check) {
        // int *found = new int[N + 1];
        bool *checked = new bool[N + 1];

        for (int i = 1; i <= N; i++) {
            checked[i] = false;
        }

        bool ok = true;
        // int time = 0;

        for (int i = 0; i < to_check.size(); i++) {
            checked[to_check[i]] = true;
            // dfs(to_check[i], found, time, ok));
            for (int neigh : adj[to_check[i]]) {
                if (checked[neigh] == true) {
                    ok = false;
                    cout << "NU\n";
                    return;
                }
            }
        }

        cout << (ok ? "DA\n" : "NU\n");
    }

 private:
    // bool dfs(int node, int found[], int &time, bool &ok) {
    //     found[node] = ++time;
    //     cout << node << endl;

    //     for (int neigh : adj[node]) {
    //         if (found[neigh] < found[node]) {
    //             cout << neigh << endl;
    //         }

    //         dfs(neigh, found, time);
    //     }
    // }
};

/*
5 6 2
1 3
1 4
3 5
5 2
4 2
1 2
1 2 4 5 3
1 3 4 5 2
*/

int main()
{
    int N, M, P;
	cin >> N >> M >> P;

    Graph g(N);

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;

        g.addEdge(u, v);
    }

    vector<int> *to_check = new vector<int>[P];
    for (int i = 0; i < P; i++) {
        int n;
        for (int j = 0; j < N; j++) {
            cin >> n;
            to_check[i].push_back(n);
        }
    }
    
    for (int i = 0; i < P; i++) {
        g.isTopologicalSort(to_check[i]);
    }

	return 0;
}
