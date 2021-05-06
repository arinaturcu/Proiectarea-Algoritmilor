#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, x, y;

    void read_input() {
        ifstream fin("in");
        fin >> n >> x >> y;
        fin.close();
    }

    int get_value(int n, int x, int y) {
        // TODO: Calculati valoarea de pe pozitia (x, y) din matricea de dimensiune 2^n x 2^n

        int p = (1 << (n - 1));
        if(n == 1) {
            if(x == 1 && y == 1)
                return 1;
            else if(x == 1 && y == 2)
                return 2;
            else if(x == 2 && y == 1)
                return 3;
            else return 4;

        }

        if(x > p && y > p)
            return 3 * p * p + get_value(n - 1, x - p, y - p);
        else if(x > p && y <= p)
            return 2 * p * p + get_value(n - 1, x - p, y);
        else if(x <= p && y > p)
            return p * p + get_value(n - 1, x, y - p);
        else return get_value(n - 1, x , y);
    }

    int get_result() { return get_value(n, x, y); }

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
