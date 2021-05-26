#include <bits/stdc++.h>
using namespace std;

struct person {
    string name;
    vector<string> addresses;
};

class Adrese {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    static constexpr int NMAX = 1001;

    int n;
    unordered_map<string, vector<int>> address_ids;
    unordered_map<int, person> id_person;
    vector<int> adj[NMAX];

    void read_input() {
        ifstream fin("adrese.in");

        int id = 1;
        fin >> n;

        for (int i = 0; i < n; i++) {
            string name;
            int add_no;

            fin >> name >> add_no;

            person new_person;
            new_person.name = name;

            for (int j = 0; j < add_no; j++) {
                string address;
                fin >> address;

                new_person.addresses.push_back(address);
            }

            id_person.insert({ id, new_person });

            for (string a : new_person.addresses) {
                vector<int> ids;

                if (address_ids.find(a) != address_ids.end()) {
                    ids = address_ids.at(a);
                    address_ids.erase(a);
                }

                ids.push_back(id);
                address_ids.insert({ a, ids });
            }

            id++;
        }

        fin.close();
    }

    void add_edge(int id1, int id2) {
        adj[id1].push_back(id2);
        adj[id2].push_back(id1);
    }

    void build_adj_list() {
        for (auto a : address_ids) {
            for (int i = 0; i < a.second.size() - 1; i++) {
                for (int j = i + 1; j < a.second.size(); j++) {
                    add_edge(a.second[i], a.second[j]);
                }
            }
        }
    }

    void dfs_recursive(int node, bool *visited, person &unif_pers) {
        for (auto neigh : adj[node]) {
            if (visited[neigh] == false) {
                visited[neigh] = true;

                person neigh_pers = id_person.at(neigh);
                if (neigh_pers.name < unif_pers.name) {
                    unif_pers.name = neigh_pers.name;
                }

                for (string addres : neigh_pers.addresses) {
                    unif_pers.addresses.push_back(addres);
                }

                dfs_recursive(neigh, visited, unif_pers);
            }
        }
    }

    vector<person> get_result() {
        build_adj_list();

        bool visited[NMAX] = {0};
        vector<person> real_persons;
        person unif_pers;

        for (int node = 1; node <= n; node++) {
            if (visited[node] == false) {
                visited[node] = true;

                unif_pers = id_person.at(node);

                dfs_recursive(node, visited, unif_pers);

                sort(unif_pers.addresses.begin(), unif_pers.addresses.end());

                unif_pers.addresses.erase(unique(unif_pers.addresses.begin(),
                    unif_pers.addresses.end()), unif_pers.addresses.end());
                real_persons.push_back(unif_pers);
            }
        }

        return real_persons;
    }

    void print_output(vector<person> real_persons) {
        ofstream fout("adrese.out");

        sort(real_persons.begin(), real_persons.end(),
            [](person p1, person p2) {
                if (p1.addresses.size() == p2.addresses.size()) {
                    return p1.name < p2.name;
                }
                return p1.addresses.size() < p2.addresses.size();
            });

        fout << real_persons.size() << endl;

        for (int i = 0; i < real_persons.size(); i++) {
            fout << real_persons[i].name << " " <<
                    real_persons[i].addresses.size() << endl;

            for (auto address : real_persons[i].addresses) {
                fout << address << endl;
            }
        }

        fout.close();
    }
};

int main() {
    auto* adrese = new (nothrow)Adrese();

    if (!adrese) {
        cerr << "new failed\n";
        return -1;
    }

    adrese->solve();
    delete adrese;
    return 0;
}
