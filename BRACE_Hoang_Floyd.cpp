#include <bits/stdc++.h>

using namespace std;

const int nxm = 1e2 + 10, oo = 1e9;
vector <tuple<int, int, int> > e;
int d[nxm][nxm], trace[nxm][nxm], n, m, k;
void solve()
{
    cin >> n >> m >> k;
    for(int i = 1; i <= 100; i++)
        for(int j = 1; j <= 100; j++)
        {
            d[i][j] = oo, trace[i][j] = i;
            if(i == j)
                d[i][j] = 0;
        }
    for(int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        d[u][v] = d[v][u] = w;
    }
    for(int k = 1; k <= n; k++)
        for(int u = 1; u <= n; u++)
            for(int v = 1; v <= n; v++)
                if(d[u][v] > d[u][k] + d[k][v])
                {
                    d[u][v] = d[u][k] + d[k][v];
                    trace[u][v] = trace[k][v];
                }
    for(int i = 1; i <= k; i++)
    {
        int a, u, v;
        cin >> a >> u >> v;
        if(a == 0)
            cout << d[u][v] << "\n";
        else
        {
            int t = v;
            stack <int> s;
            while(t != u)
            {
                s.push(t);
                t = trace[u][t];
            }
            cout << s.size() + 1 << " " << u << " ";
            while(s.size())
            {
                cout << s.top() << " ";
                s.pop();
            }
            cout << "\n";
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--)
        solve();
    return 0;
}
