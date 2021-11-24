#include <bits/stdc++.h>
using namespace std;
FILE *fi = freopen("brace.inp","r",stdin);
FILE *fo = freopen("brace_B.out","w",stdout);

const int maxN = 110;
typedef pair<int, int> ii;
int numNode, numEdge, numTest;
int d[maxN][maxN];
int trace[maxN][maxN];
stack <int> st;
vector <ii> g[maxN];
priority_queue <ii, vector<ii>, greater<ii>> pq;

void dijkstra(int s) {
    int u, du;
    for (int i = 1; i <= numNode; i++) d[s][i] = 1e9;
    d[s][s] = 0;
    pq.push({0, s});
    while (pq.size()) {
        u = pq.top().second;
        du = pq.top().first;
        pq.pop();
        if (du != d[s][u]) continue;
        for (ii v : g[u])
            if (d[s][v.second] > du + v.first) {
                d[s][v.second] = du + v.first;
                trace[s][v.second] = u;
                pq.push({d[s][v.second], v.second});
            }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    bool type;
    int u, v, cost;
    cin >> numNode >> numEdge >> numTest;
    for (int i = 1; i <= numEdge; i++) {
        cin >> u >> v >> cost;
        g[u].push_back({cost, v});
        g[v].push_back({cost, u});
    }
    for (int i = 1; i <= numNode; i++) dijkstra(i);
    while (numTest--) {
        cin >> type >> u >> v;
        if (type) {
            while (v != u) {
                st.push(v);
                v = trace[u][v];
            }
            st.push(u);
            cout << st.size() << " ";
            while (st.size()) {
                cout << st.top() << " ";
                st.pop();
            }
            cout << "\n";
        }
        else cout << d[u][v] << "\n";
    }
}
