#include <bits/stdc++.h>
using namespace std;

static constexpr int NMAX = 1e4 + 1;

class Graph {
 public:
    int N;
    vector<int> adj[NMAX];

    explicit Graph(int N) {
        this->N = N;
    }

    void add_edge(int src, int dst) {
        adj[src].push_back(dst);
        adj[dst].push_back(src);
    }

    void cv_dfs(int node, int found[], int low_link[], int parent[],
                int &time, bool CVs[]) {
        found[node] = ++time;
        low_link[node] = found[node];

        int children = 0;

        for (int neigh : adj[node]) {
            if (parent[neigh] != -1) {
                if (neigh != parent[node]) {
                    low_link[node] = min(low_link[node], found[neigh]);
                }

                continue;
            }

            parent[neigh] = node;
            children++;

            cv_dfs(neigh, found, low_link, parent, time, CVs);

            low_link[node] = min(low_link[node], low_link[neigh]);

            // daca nu e radacina si nu exista drum pe muchii neumblate
            // de la el la un stramos, este CV
            if (parent[node] != node && low_link[neigh] >= found[node]) {
                CVs[node] = true;
            }
        }

        // daca e radacina si are cel putin 2 copii
        if (parent[node] == node && children >= 2) {
            CVs[node] = true;
        }
    }

    bool* get_cut_vertices() {
        int found[NMAX];
        int low_link[NMAX];
        int parent[NMAX];
        // unordered_set<int> *CVs = new unordered_set<int>();
        bool *CVs = (bool *)calloc(NMAX, sizeof(bool));

        for (int i = 1; i < N + 1; i++) {
            found[i] = INT32_MAX;
            low_link[i] = INT32_MAX;
            parent[i] = -1;
        }

        int time = 0;
        parent[1] = 1;  // conventie;
        cv_dfs(1, found, low_link, parent, time, CVs);

        return CVs;
    }
};

class Retea {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    Graph *graph;

    void read_input() {
        ifstream fin("retea.in");

        int m;
        fin >> n >> m;

        graph = new Graph(n);

        int src, dst;
        for (int i = 0; i < m; i++) {
            fin >> src >> dst;
            graph->add_edge(src, dst);
        }

        fin.close();
    }

    void dfs_deleted_node(bool *visited, int node, int deleted, int &nodes) {
        visited[node] = true;
        nodes++;

        for (auto neigh : graph->adj[node]) {
            if (!visited[neigh] && node != deleted) {
                dfs_deleted_node(visited, neigh, deleted, nodes);
            }
        }
    }

    void reset_visited(bool *visited) {
        for (int i = 1; i <= n; i++) {
            visited[i] = false;
        }
    }

    int* get_result() {
        bool *CVs = graph->get_cut_vertices();
        int *result = (int *) malloc((n + 1) * sizeof(int));
        bool visited[NMAX] = { false };
        int count;

        for (int node = 1; node <= n; node++) {
            if (!CVs[node]) {  // daca nu este CV
                result[node] = 2 * (n - 1);
                continue;
            }

            // daca este CV trebuie sa aflu componentele conexe ramase
            reset_visited(visited);
            visited[node] = true;
            int conex_comp = 0;

            count = 0;
            for (int i = 1; i <= n; i++) {
                if (!visited[i]) {
                    conex_comp = 0;

                    dfs_deleted_node(visited, i, node, conex_comp);

                    // toate apelurile initiate de componenta conexa
                    count += conex_comp * (n - conex_comp);
                }
            }

            count += n - 1;  // toate apelurile initiate de nodul eliminat
            result[node] = count;
        }

        return result;
    }

    void print_output(int* result) {
        ofstream fout("retea.out");
        for (int i = 1; i <= n; i++) {
            fout << result[i] << endl;
        }
        fout.close();
    }
};

int main() {
    auto* retea = new (nothrow)Retea();

    if (!retea) {
        cerr << "new failed\n";
        return -1;
    }

    retea->solve();
    delete retea;
    return 0;
}
