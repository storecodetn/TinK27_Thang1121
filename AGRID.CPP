#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };
int n, m, X, Y, U, V;
int d[N][N]; // d[i][j]=độ dài đường đi từ ngắn nhất (x, y) -> (u, v)
char ch[N][N]; // lưới
queue<pair<int, int>> q[10]; // mảng hàng đợi - K = 9
bool color[N][N]; // đánh dấu các ô trong lưới, ban đầu khởi tạo false
bool inGrid(int r, int c) {
    if (r >= 1 && r <= n && c >= 1 && c <= m) return true;
    return false;
}
int weight(char c) {
    if (c == 'R' || c == 'G') return 0;
    return c - 48;
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
            d[i][j] = 10 * (n + m);
        }
    }
    q[0].push({ X, Y }); // đưa ô (X, Y) vào hàng đợi q[0]
    d[X][Y] = 0;
    int ptr = 0;
    while (true) {
        int cycle = ptr;
        while (q[ptr].empty()) {
            ptr = (ptr + 1) % 10;
            if (ptr == cycle) break;
        }
        if (q[ptr].empty()) break;
        int x = q[ptr].front().first;
        int y = q[ptr].front().second;
        q[ptr].pop(); // lấy ô (x, y) ra khỏi hàng đợi 
        if (color[x][y]) continue;
        color[x][y] = true;
        for (int i = 0; i < 4; i++) {
            int u = x + dx[i],v = y + dy[i];//xét ô (u,v) kề với (x,y)
            if (!inGrid(u, v) || color[u][v]) continue;
            d[u][v] = min(d[u][v], d[x][y] + weight(ch[u][v]));
            q[(ptr + weight(ch[u][v])) % 10].push({u, v});
        }
    }
    cout << d[U][V];
}
