#include <bits/stdc++.h>
using namespace std;

class Inv {
public:
    void solve() {
        read_input();
        print_response(merge_sort(0, v.size() - 1));
    }

private:
    int n;
    vector<int> v;

    int merge_halves(int left, int right) {
        int mid = (left + right) / 2;
        vector<int> aux;
        int i = left, j = mid + 1;
        int count_inversions = 0;

        while (i <= mid && j <= right) {
            if (v[i] <= v[j]) {
                aux.push_back(v[i]);
                i++;
            } else {
                count_inversions += mid - i + 1;
                aux.push_back(v[j]);
                j++;
            }
        }

        while (i <= mid) {
            aux.push_back(v[i]);
            i++;
        }

        while (j <= right) {
            aux.push_back(v[j]);
            j++;
        }

        for (int k = left; k <= right; k++) {
            v[k] = aux[k - left];
        }

        return count_inversions;
    }


    int merge_sort(int left, int right) {
        int count_inversions = 0;

        if (left >= right) return count_inversions;
        int mid = (left + right) / 2;

        count_inversions += merge_sort(left, mid);
        count_inversions += merge_sort(mid + 1, right);
        count_inversions += merge_halves(left, right);

        return count_inversions % 9917;
    }

    void read_input () {
        ifstream in("inv.in");
        in >> n;
        for (int i = 0, e; i < n; ++i) {
            in >> e;
            v.push_back(e);
        }
        in.close();
    }

    void print_response(int n) {
        ofstream out("inv.out");
        out << n % 9917 << endl;
        out.close();
    }
};

int main () {
    Inv *inv = new Inv{};
    inv->solve();

    return 0;
}

