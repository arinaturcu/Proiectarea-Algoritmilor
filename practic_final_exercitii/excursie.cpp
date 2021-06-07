#include<iostream>
#include <list>
#include <stack>
using namespace std;

#define NMAX 302

void go(int costs[NMAX][NMAX], int N, int K, int src_i, int src_j, int curr_cost, int depth, int &min_cost) {
    if (depth == K) {
        if (curr_cost < min_cost) {
            min_cost = curr_cost;
        }
        
        return;
    }
    
    if (src_i + 1 < N) {
        go(costs, N, K, src_i + 1, src_j, curr_cost + costs[src_i + 1][src_j], depth + 1, min_cost);
    }

    if (src_i + 1 < N && src_j + 1 < N) {
        go(costs, N, K, src_i + 1, src_j + 1, curr_cost + costs[src_i + 1][src_j + 1], depth + 1, min_cost);
    }

    if (src_j + 1 < N) {
        go(costs, N, K, src_i, src_j + 1, curr_cost + costs[src_i][src_j + 1], depth + 1, min_cost);
    }
}

int main() {
    int N, K;
    int min_cost = 0xfffffff;

    cin >> N >> K;

    int costs[NMAX][NMAX];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> costs[i][j];
        }
    }

    go(costs, N, K, 0, 0, costs[0][0], 1, min_cost);

    cout << min_cost << endl;

	return 0;
}
