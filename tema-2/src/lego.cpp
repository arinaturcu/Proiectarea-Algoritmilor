#include <bits/stdc++.h>
using namespace std;

class Lego {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int K;
    int N;
    int T;

    void read_input() {
        ifstream fin("lego.in");
        fin >> K >> N >> T;
        fin.close();
    }

    void find_combinations(vector<vector<int>> &combs, vector<int> &selected,
                           int start, int remain) {
        if (remain == 0) {
            combs.push_back(selected);
            return;
        }

        for (int i = start; i <= K - remain; i++) {
            selected.push_back(i + 1);
            find_combinations(combs, selected, i + 1, remain - 1);
            selected.pop_back();
        }
    }

    void find_all_combs(vector<int> choose_from, vector<vector<int>> &combs,
                        vector<int> &selected, int start, int remain) {
        if (remain >= 0 && remain < T) {
            combs.push_back(selected);
        }

        if (remain == 0) return;

        for (int i = start; i < N; i++) {
            selected.push_back(choose_from.at(i));
            find_all_combs(choose_from, combs, selected, i, remain - 1);
            selected.pop_back();
        }
    }

    int max_consecutive(vector<int> terms) {
        // max sum is (last element times N)
        bool *is_sum = (bool *)calloc(terms.back() * T + 1, sizeof(bool));
        vector<vector<int>> combs;
        vector<int> selected;

        find_all_combs(terms, combs, selected, 0, T);
        for (auto c : combs) {
            int sum = 0;
            for (int n : c) {
                sum += n;
            }

            is_sum[sum] = true;
        }

        int max_count = 0;
        int cons_count = 0;

        for (int i = 1; i <= terms.back() * T; i++) {
            if (!is_sum[i]) {
                if (cons_count > max_count) {
                    max_count = cons_count;
                }
                cons_count = 0;
                continue;
            }
            cons_count++;
        }

        if (is_sum[terms.back() * T] && cons_count > max_count) {
            max_count = cons_count;
        }

        free(is_sum);
        return max_count;
    }

    pair <int, vector<int>> get_result() {
        vector<int> selected;
        vector<vector<int>> combs;
        int max_cons = 0;

        find_combinations(combs, selected, 1, N - 1);
        for (auto c : combs) {
            c.insert(c.begin(), 1);

            int curr_cons = max_consecutive(c);
            if (curr_cons > max_cons) {
                max_cons = curr_cons;
                selected = c;
            }
        }

        return pair<int, vector<int>>(max_cons, selected);
    }

    void print_output(pair <int, vector<int>> result) {
        ofstream fout("lego.out");

        fout << result.first << endl;
        for (int n : result.second) {
            fout << n << " ";
        }

        fout.close();
    }
};

int main() {
    auto* lego = new (nothrow)Lego();

    if (!lego) {
        cerr << "new failed\n";
        return -1;
    }

    lego->solve();
    delete lego;
    return 0;
}
