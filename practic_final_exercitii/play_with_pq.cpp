// program in c++ to use priority_queue with structure

#include <iostream>
#include <queue>
using namespace std;
#define ROW 5
#define COL 2

struct Person {
	int age;
	float height;
};

// this is an strucure which implements the
// operator overloading
struct CompareHeight {
	bool operator()(Person const& p1, Person const& p2) {
		return p1.height < p2.height;
	}
};

int main()
{
	priority_queue<Person, vector<Person>, CompareHeight> Q;

	// When we use priority_queue with structure
	// then we need this kind of syntax where
	// CompareHeight is the functor or comparison function
	float arr[ROW][COL] = { { 30, 5.5 }, { 25, 5 },
					        { 20, 6   }, { 33, 6.1 }, { 23, 5.6 } };

	for (int i = 0; i < ROW; ++i) {
        Person p;
        p.age = arr[i][0];
        p.height = arr[i][1];

		Q.push(Person(p));

		// insert an object in priority_queue by using
		// the Person strucure constructor
	}

	while (!Q.empty()) {
		Person p = Q.top();
		Q.pop();
		cout << p.age << " " << p.height << "\n";
	}
	return 0;
}
