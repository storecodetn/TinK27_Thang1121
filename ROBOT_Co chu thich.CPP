#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1000 + 1;
int dx[] = { -1, 0, 0, 1 };
int dy[] = { 0, -1, 1, 0 };

int n, l1, c1, l2, c2;
bool a[N][N];
int d1[N][N][4], d2[N][N][4];

struct State {
    int x, y, z; 
};

bool inGrid(int x, int y) {
    return (x >= 1 && x <= n && y >= 1 && y <= n);
}


void bfs(int X, int Y, int d[][N][4]) {
    deque<State> dq;

    for (int i = 0; i < 4; i++) {
        dq.push_back({X, Y, i});
        d[X][Y][i] = 0;
    }

    while (!dq.empty()) {
        int x = dq.front().x;
        int y = dq.front().y;
        int z = dq.front().z;
        dq.pop_front();

        if (!a[x][y]) {
            int u = x + dx[z], v = y + dy[z];
            if (inGrid(u, v) && d[u][v][z] > d[x][y][z]) {
                d[u][v][z] = d[x][y][z];
                dq.push_front({u, v, z});
            }
        }

        for (int i = 0; i < 4; i++) if (i != z) {
            if (d[x][y][i] > d[x][y][z] + 1) {
                d[x][y][i] = d[x][y][z] + 1;
                dq.push_back({x, y, i});
            }
        }
    }
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            for (int k = 0; k < 4; k++)
                d1[i][j][k] = d2[i][j][k] = 4 * n * n;
        }
    
    cin >> l1 >> c1 >> l2 >> c2;
    bfs(l1, c1, d1);
    bfs(l2, c2, d2);
    
    int ans1 = 4 * n * n, ans2 = 4 * n * n, ans3 = 0;
    //ans1: số lần đổi hướng ít nhất đi từ ô (l1,c1) --> (l2,c2)
    //ans2: Số lần đổi hướng ít nhất của một ô bị cản (i,j) khi đi từ (l1,c1) --> (l2,c2) qua (i,j)
    //ans3: Số lượng ô bị cản có số lần đổi hướng ít nhất giống nhau.
    for (int i = 0; i < 4; i++) {
        ans1 = min(ans1, d1[l2][c2][i]);
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (a[i][j]) {
                int tmp = 4 * n * n;
                for (int k = 0; k < 4; k++)
                    tmp = min(tmp, d1[i][j][k] + d2[i][j][3 - k]);
                if (ans2 > tmp) {//Ghi nhận lại xuất hiện ô bị cản (i,j) có số lần đổi hướng ít hơn
                    ans2 = tmp;//Ghi nhận số lần đổi hướng ít hơn
                    ans3 = 1;//Số lượng ô khởi tạo lại là 1
                }
                else if (ans2 == tmp) {//Nếu phát hiện ô (i,j) bị cản có số lần đổi hướng bằng với 
                                       //số lần đổi hướng ít nhất hiện tại thi tăng đếm
                    ans3++;//Tăng số lượng ô
                }
            }
    if (ans2 >= ans1) {//Nếu số lần đổi hướng ít nhất của các ô bị cản lớn hơn số lần đổi hướng khi đi từ (l1,c1) --> (l2,c2)
                       //mà không qua ô bị cản nào. khi này số lần đổi hướng ít nhất dù bỏ bất cứ ô bị cản nào cũng là ans1
                       //Trường hợp ans2<ans1 ta xuất luôn kết quả. Nghĩa là đi qua ô bị cản sẽ ít đổi hướng hơn.
        ans3 = 0;
        ans2 = ans1;//Số lần đổi hướng ít nhất dù bỏ bất cứ ô bị cản nào đều là ans1 (vì đường đi tốt nhất không qua ô bị cản nào)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                ans3 += a[i][j]; //Số lượng ô bị cản chính là đáp án câu 3.
    }
    cout << ans1 << " " << ans2 << " " << ans3;
}
