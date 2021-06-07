// A C++ program to find strongly connected components in a given
// directed graph using Tarjan's algorithm (single DFS)
#include<iostream>
#include <list>
#include <stack>
using namespace std;

class Graph {
	int V; 
	list<int> *adj;

	void SCC_dfs(int u, int disc[], int low[], stack<int> *st, bool stackMember[], int &time);
 
 public:
	Graph(int V);
	void addEdge(int v, int w);
	void SCC();
};

Graph::Graph(int V) {
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
	adj[v].push_back(w);
}

void Graph::SCC_dfs(int node, int found[], int low_link[], stack<int> *st, bool stack_member[], int &time) {
    found[node] = ++time;
    low_link[node] = found[node];
    st->push(node);
    stack_member[node] = true;

    for (int neigh : adj[node]) {
        if (found[neigh] != INT32_MAX) { // daca a mai fost vizitat
            if (stack_member[neigh]) { // daca e in stiva
                low_link[node] = min(low_link[node], found[neigh]);
            }

            continue;
        }

        SCC_dfs(neigh, found, low_link, st, stack_member, time);

        low_link[node] = min(low_link[node], low_link[neigh]);
    }

    int x; // ca sa salvez nodul extras
    if (low_link[node] == found[node]) {
        do {
            x = st->top();
            st->pop();
            stack_member[x] = false;
            cout << x << " ";
        } while(x != node);

        cout << endl;
    }
}

void Graph::SCC() {
    int *found = new int[V];
    int *low_link = new int[V];
    bool *stack_member = new bool[V];
    stack<int> *st = new stack<int>();

    for (int i = 0; i < V; i++) {
        found[i] = INT32_MAX;
        low_link[i] = INT32_MAX;
        stack_member[i] = false;
    }

    int time = 0;
    for (int i = 0; i < V; i++) {
        if (found[i] == INT32_MAX) {
            SCC_dfs(i, found, low_link, st, stack_member, time);
        }
    }
}

// Driver program to test above function
int main() {
	cout << "\nSCCs in first graph \n";
	Graph g1(5);
	g1.addEdge(1, 0);
	g1.addEdge(0, 2);
	g1.addEdge(2, 1);
	g1.addEdge(0, 3);
	g1.addEdge(3, 4);
	g1.SCC();

    // SCCs in first graph 
    // 4
    // 3
    // 1 2 0


	cout << "\nSCCs in second graph \n";
	Graph g2(4);
	g2.addEdge(0, 1);
	g2.addEdge(1, 2);
	g2.addEdge(2, 3);
	g2.SCC();

    // SCCs in second graph 
    // 3
    // 2
    // 1
    // 0

	cout << "\nSCCs in third graph \n";
	Graph g3(7);
	g3.addEdge(0, 1);
	g3.addEdge(1, 2);
	g3.addEdge(2, 0);
	g3.addEdge(1, 3);
	g3.addEdge(1, 4);
	g3.addEdge(1, 6);
	g3.addEdge(3, 5);
	g3.addEdge(4, 5);
	g3.SCC();

    // SCCs in third graph 
    // 5
    // 3
    // 4
    // 6
    // 2 1 0

	cout << "\nSCCs in fourth graph \n";
	Graph g4(11);
	g4.addEdge(0,1);g4.addEdge(0,3);
	g4.addEdge(1,2);g4.addEdge(1,4);
	g4.addEdge(2,0);g4.addEdge(2,6);
	g4.addEdge(3,2);
	g4.addEdge(4,5);g4.addEdge(4,6);
	g4.addEdge(5,6);g4.addEdge(5,7);g4.addEdge(5,8);g4.addEdge(5,9);
	g4.addEdge(6,4);
	g4.addEdge(7,9);
	g4.addEdge(8,9);
	g4.addEdge(9,8);
	g4.SCC();

    // SCCs in fourth graph 
    // 8 9
    // 7
    // 5 4 6
    // 3 2 1 0
    // 10

	cout << "\nSCCs in fifth graph \n";
	Graph g5(5);
	g5.addEdge(0,1);
	g5.addEdge(1,2);
	g5.addEdge(2,3);
	g5.addEdge(2,4);
	g5.addEdge(3,0);
	g5.addEdge(4,2);
	g5.SCC();

    // SCCs in fifth graph 
    // 4 3 2 1 0

	return 0;
}
