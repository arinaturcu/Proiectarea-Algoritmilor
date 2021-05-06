#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, m;
    vector<int> dist;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 0, d; i < n; i++) {
            fin >> d;
            dist.push_back(d);
        }
        fin.close();
    }

    int get_result() {
        // DONE: Aflati numarul minim de opriri necesare pentru a ajunge
        //  la destinatie.

        int r = m; // remaining
        int stops = 0;

        for (int i = 0; i < n - 1; ++i) {
            if (i == 0) {
                if ((r - dist[i]) < (dist[i + 1] - dist[i])) {
                    // refill
                    r = m;
                    stops++;
                } else {
                    r -= dist[i];
                }
            } else {
                // if it won't have enough to go to the next destination
                if ((r - (dist[i] - dist [i - 1])) < (dist[i + 1] - dist[i])) {
                    // refill
                    r = m;
                    stops++;
                } else {
                    r -= (dist[i] - dist [i - 1]);
                }
            }
        }

        return stops;
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result;
        fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main() {
    // * se aloca un obiect Task pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (std::nothrow) Task(); // hint: cppreference/nothrow
    if (!task) {
        std::cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
