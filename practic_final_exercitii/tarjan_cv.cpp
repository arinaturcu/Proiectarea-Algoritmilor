// A C++ program to find cut vertexes (Articulation Points) in a given
// directed graph using Tarjan's algorithm (single DFS)

// decate ori apare un cv, atatea componente conexe apar in plus daca
// il eliminam
#include <bits/stdc++.h>
using namespace std;

class Graph {
	int V; 
	list<int> *adj;

	void AP_dfs(int u, int disc[], int low[], int parent[], int &time, unordered_set<int> *CSv);
 
 public:
	Graph(int V);
	void addEdge(int v, int w);
	void AP();
};

Graph::Graph(int V) {
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
	adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::AP_dfs(int node, int found[], int low_link[], int parent[], int &time, unordered_set<int> *CVs) {
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

        AP_dfs(neigh, found, low_link, parent, time, CVs);

        low_link[node] = min(low_link[node], low_link[neigh]);

        // daca nu e radacina si nu exista drum pe muchii neumblate
        // de la el la un stramos, este CV
        if (parent[node] != node && low_link[neigh] >= found[node]) {
            CVs->insert(node);
        }
    }

    // daca e radacina si are cel putin 2 copii
    if (parent[node] == node && children >= 2) {
        CVs->insert(node);
    }
}

void Graph::AP() {
    int *found = new int[V];
    int *low_link = new int[V];
    int *parent = new int[V];
    unordered_set<int> *CVs = new unordered_set<int>();

    for (int i = 0; i < V; i++) {
        found[i] = INT32_MAX;
        low_link[i] = INT32_MAX;
        parent[i] = -1;
    }

    int time = 0;
    for (int i = 0; i < V; i++) {
        if (parent[i] == -1) {
            parent[i] = i; // conventie;
            AP_dfs(i, found, low_link, parent, time, CVs);
        }
    }

    for (int cv : *CVs) {
        cout << cv << " ";
    }

    cout << endl;
}

// Driver program to test above function
int main() {
	// Create graphs given in above diagrams
    cout << "\nArticulation points in first graph \n";
    Graph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(2, 1);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    g1.AP();
 
    cout << "\nArticulation points in second graph \n";
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.AP();
 
    cout << "\nArticulation points in third graph \n";
    Graph g3(7);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(2, 0);
    g3.addEdge(1, 3);
    g3.addEdge(1, 4);
    g3.addEdge(1, 6);
    g3.addEdge(3, 5);
    g3.addEdge(4, 5);
    g3.AP();

    /**  
     * ref:
     * 
     *  Articulation points in first graph
     *  0 3
     * 
     *  Articulation points in second graph
     *  1 2
     * 
     *  Articulation points in third graph
     *  1
     * 
     */

	return 0;
}
