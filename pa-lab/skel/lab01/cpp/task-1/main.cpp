#include <bits/stdc++.h>
using namespace std;
 
class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }
 
private:
    int n, x;
    vector<int> v;
 
    void read_input() {
        ifstream fin("in");
        fin >> n;
        for (int i = 0, e; i < n; i++) {
            fin >> e;
            v.push_back(e);
        }
        fin >> x;
        fin.close();
    }
 
    int find_first() {
        int left = 0;
        int right = n - 1;
        int first = -1;
        int mid;

        while (left <= right) {
            mid = (int)(1LL * (right + left) / 2);

            if (v[mid] == x) {
                first = mid;
                right = mid - 1;
                continue;
            }
            if (v[mid] < x) {
                left = mid + 1;
                continue;
            }
            if (v[mid] > x) {
                right = mid - 1;
            }
        }

        return first;
    }
 
    int find_last() {
        int left = 0;
        int right = n - 1;
        int last = -1;
        int mid;

        while (left <= right) {
            mid = (int)(1LL * (right + left) / 2);

            if (v[mid] == x) {
                last = mid;
                left = mid + 1;
                continue;
            }
            if (v[mid] < x) {
                left = mid + 1;
                continue;
            }
            if (v[mid] > x) {
                right = mid - 1;
            }
        }

        return last;
    }
 
    int get_result() {
        int first = find_first();
        int last = find_last();
        if (first == -1 || last == -1) {
            return 0;
        }
        return last - first + 1;
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
        std::cerr << "new failed\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}