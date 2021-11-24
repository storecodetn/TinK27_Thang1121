#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };
int n, m, X, Y, U, V;
int d[N][N]; // d[i][j] = độ dài đường đi từ ngắn nhất (x, y) -> (u, v)

char ch[N][N]; // lưới

deque<pair<int, int>> q; // hàng đợi hai đầu - sử dụng CTDL pair (first - hàng, second - cột)
bool color[N][N]; // đánh dấu các ô trong lưới, ban đầu khởi tạo false
bool inGrid(int r, int c) {
    if (r >= 1 && r <= n && c >= 1 && c <= m) return true;
    return false;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> ch[i][j];
            if (ch[i][j] == 'G')
                X = i, Y = j;
            else if (ch[i][j] == 'R')
                U = i, V = j;
            d[i][j] = n + m;
        }
    }
    q.push_back({ X, Y }); // đưa ô (X, Y) vào hàng đợi
    d[X][Y] = 0;
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop_front(); // lấy ô (x, y) ra khỏi hàng đợi 
        if (color[x][y]) continue;
        color[x][y] = true;
        for (int i = 0; i < 4; i++) {
            int u = x + dx[i],v = y + dy[i];//xét ô (u,v) kề với (x,y)
            if (!inGrid(u, v) || color[u][v]) continue;
            if (ch[u][v] == '*') q.push_back({ u, v });
            else q.push_front({ u, v });
            d[u][v] = min(d[u][v], d[x][y] + (ch[u][v] == '*'));
        }
    }

    cout << d[U][V];
}
