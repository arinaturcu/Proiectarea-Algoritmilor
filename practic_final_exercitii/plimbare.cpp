#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

const int LimN = 1005, LimD = 5005;

int n, m, d, Gx, Gy, Ix, Iy, mat[LimN][LimN], pasi[LimN][LimN], gigel[LimD], ionel[LimD];

int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
queue<pair<int, int>> q;

int inside(int x, int y)
{
    return 1 <= x && x <= n && 1 <= y && y <= m;
}

void bfs(int x, int y, int aux[])
{
    pasi[x][y] = 1;
    aux[1] = mat[x][y];
    q.push({x, y});

    while(q.empty() == 0)
    {
        x = q.front().first;
        y = q.front().second;
        q.pop();
        for(int i = 0; i < 4; ++i)
            if(inside(x + dx[i], y + dy[i]) && pasi[ x + dx[i] ][ y + dy[i] ] == 0)
            {
                pasi[ x + dx[i] ][ y + dy[i] ] = pasi[x][y] + 1;
                aux[ pasi[ x + dx[i] ][ y + dy[i] ] ] = max(aux[ pasi[ x + dx[i] ][ y + dy[i] ] ], mat[ x + dx[i] ][ y + dy[i] ]);
                q.push({x + dx[i], y + dy[i]});
            }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);

    cin >> n >> m >> d >> Gx >> Gy >> Ix >> Iy;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            cin >> mat[i][j];
    bfs(Gx, Gy, gigel);
    for(int i = 1; i <= n; ++i)
        memset(pasi[i], 0, sizeof(pasi[i]));
    bfs(Ix, Iy, ionel);
    int maxim = 0;
    for(int i = 1; i <= d + 1; ++i)
        for(int j = 1; j<= d - i + 2; ++j)
            maxim = max(maxim, gigel[i] + ionel[j]);
    cout << maxim;
    return 0;
}
