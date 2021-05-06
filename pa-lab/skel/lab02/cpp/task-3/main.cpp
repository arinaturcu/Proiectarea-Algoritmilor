#include <bits/stdc++.h>
using namespace std;

struct Homework {
    int deadline;
    int score;

    Homework(int _deadline, int _score)
        : deadline(_deadline)
        , score(_score) { }
};

bool sorting_function(Homework h1, Homework h2) {
    if (h1.score > h2.score) {
        return true;
    } else if (h1.score < h2.score) {
        return false;
    } else {
        return (h1.deadline < h2.deadline);
    }
}

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n;
    vector<Homework> hws;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        for (int i = 0, deadline, score; i < n; i++) {
            fin >> deadline >> score;
            hws.push_back(Homework(deadline, score));
        }
        fin.close();
    }

    int get_result() {
        // DONE: Aflati punctajul maxim pe care il puteti obtine planificand
        // optim temele.

        int total = 0;

        sort (hws.begin(), hws.end(), sorting_function);

        bool *weeks = (bool *)calloc(sizeof(bool), n + 1);
        
        // incerc sa pun o tema cu deadline mare cat mai tarziu posibil
        for (int j = 0; j < n; ++j) {
            // daca nu e nimic in saptmana cu deadline-ul
            if (weeks[hws[j].deadline] == 0) 
            {
                total += hws[j].score;
                weeks[hws[j].deadline] = 1;
            } 
            else 
            {   
                // incerc sa o pun intr-o saptamana libera mai devreme
                int w = hws[j].deadline - 1;
                while (weeks[w] == 1 && w > 0)
                {
                    w--;
                }

                if (weeks[w] == 0 && w > 0) {
                    total += hws[j].score;
                    weeks[w] = 1;
                }
            }
        }

        free(weeks);
        return total;
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
