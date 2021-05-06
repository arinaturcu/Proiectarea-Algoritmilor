#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    double n;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        fin.close();
    }

    double get_result() {
        // DONE: Calculati sqrt(n) cu o precizie de 0.001
        // Precizie de 10^-x = |rezultatul vostru - rezultatul corect| <= 10^-x

//        double precision = 0.0009;
//        if (n >= 1) {
//            // interval [1, n]
//            double left = 1.0;
//            double right = n;
//
//            while (left <= right) {
//                double mid = (left + right) / 2;
//                if (abs(mid * mid - n) <= precision) {
//                    return mid;
//                }
//                if (mid * mid > n) {
//                    right = mid;
//                }
//                if (mid * mid < n) {
//                    left = mid;
//                }
//            }
//        } else {
//            double left = n;
//            double right = 1.0;
//
//            while (left <= right) {
//                double mid = (left + right) / 2;
//                cout << mid << " " << mid * mid << endl;
//                if (abs(mid * mid - n) < precision) {
//                    return mid;
//                }
//                if (mid * mid > n) {
//                    right = mid;
//                }
//                if (mid * mid < n) {
//                    left = mid;
//                }
//            }
//        }

        double precision = 0.0009;
        double mid;
        double left;
        double right;

        if (n >= 1) {
            left = 1;
            right = n;

            while (left <= right) {
                mid = (left + right) / 2;

                if (abs((mid * mid) - n) < precision) {
                    return mid;
                }
                if (mid * mid < n) {
                    left = mid;
                    continue;
                }
                if (mid * mid > n) {
                    right = mid;
                }
            }
        } else {
            left = n;
            right = 1;

            while (left <= right) {
                mid = (left + right) / 2;

                if (abs((mid * mid) - n) < precision) {
                    return mid;
                }
                if (mid * mid < n) {
                    left = mid;
                    continue;
                }
                if (mid * mid > n) {
                    right = mid;
                }
            }
        }

        return 0;
    }

    void print_output(double result) {
        ofstream fout("out");
        fout << setprecision(4) << fixed << result;
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
