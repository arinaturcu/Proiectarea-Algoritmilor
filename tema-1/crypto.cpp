#include <bits/stdc++.h>
using namespace std;

struct specs {
    int power;
    int upgrade_price;
};

class Crypto {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int num, budget;
    vector<specs> computers;

    void read_input() {
        ifstream fin("crypto.in");
        fin >> num >> budget;

        for (int i = 0; i < num; ++i) {
            specs c;
            fin >> c.power >> c.upgrade_price;

            computers.push_back(c);
        }

        fin.close();
    }

    void upgrade(specs *c, int times) {
        c->power += times;
    }

    static int comp_function(specs c1, specs c2) {
        return c1.power < c2.power;
    }

    int get_result() {
        sort(computers.begin(), computers.end(), comp_function);

        int min_power = computers[0].power;
        int min_power_price = 0;
        int next_power = min_power;

        while (budget > 0) {
            min_power_price = 0;

            for (int i = 0; i < num; ++i) {
                if (computers[i].power != min_power) {
                    next_power = computers[i].power;
                    break;
                }

                min_power_price += computers[i].upgrade_price;
            }

            int times = (next_power == min_power) ? budget / min_power_price :
                min(next_power - min_power, budget / min_power_price);

            if (times < 1) return min_power;

            for (int i = 0; i < num; ++i) {
                if (computers[i].power == min_power) {
                    upgrade(&computers[i], times);
                } else {
                    break;
                }
            }

            budget -= min_power_price * times;
            min_power += times;
        }

        return min_power;
    }

    void print_output(int result) {
        ofstream fout("crypto.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto* crypto = new Crypto();

    crypto->solve();
    delete crypto;
    return 0;
}
