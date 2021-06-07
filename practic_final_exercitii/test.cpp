#include <bits/stdc++.h>
using namespace std;

bool isPath(int x0, int y0, int x1, int y1) {
    if (x0 == x1 && y0 == y1) {
        return true;
    }

    if (x0 > x1 || y0 > y1) {
        return false;
    }
    
    if (isPath(x0 + y0, y0, x1, y1)) {
        return true;
    }
    
    if (isPath(x0, x0 + y0, x1, y1)) {
        return true;
    }
    
    return false;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int x0, y0;
    int x1, y1;
    
    cin >> x0 >> y0 >> x1 >> y1;
    
    cout << (isPath(x0, y0, x1, y1) ? "Yes" : "No");
    
    return 0;
}