#include<bits/stdc++.h>
using namespace std;
int n,a[1001][1001],l1,c1,l2,c2,d1[1001][1001][4],d2[1001][1001][4],cnt=0;
int dr[4]={-1,0,0,1};
int dc[4]={0,-1,1,0};
struct TP{
    int u,v,w;
};
bool check(int p,int q){
    return (1<=p && p<=n) && (1<=q && q<=n);
}
int main(){
    ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            if(a[i][j]) cnt++;
            for(int h=0;h<=3;h++){
                d2[i][j][h]=1e9;
                d1[i][j][h]=1e9;
            }
        }
    }
    cin>>l1>>c1>>l2>>c2;
    queue<TP> qu;
    for(int i=0;i<=3;i++){
        qu.push({l1,c1,i});
        d1[l1][c1][i]=0;
    }
    while(qu.size()){
        int u=qu.front().u;
        int v=qu.front().v;
        int w=qu.front().w;
        qu.pop();
        if(a[u][v]==1) continue;
        int p=u+dr[w];
        int q=v+dc[w];
        if(check[p][q]){
            if(d1[p][q][w]>d1[u][v][w]){
                d1[p][q][w]=d1[u][v][w];
                qu.push({p,q,w});
            }
        }
        for(int i=0;i<=3;i++){
            if(i==w) continue;
            int p=u+dr[i];
            int q=v+dc[i];
            if(!check(p,q)) continue;
            if(d1[p][q][i]>d1[u][v][w]+1){
                d1[p][q][i]=d1[u][v][w]+1;
                qu.push({p,q,i});
            }
        }
    }
    int ans=1e9;
    for(int i=0;i<=3;i++){
        ans=min(ans,d1[l2][c2][i]);
    }
    cout<<ans<<" ";
    for(int i=0;i<=3;i++){
        qu.push({l2,c2,i});
        d2[l2][c2][i]=0;
    }
    while(qu.size()){
        int u=qu.front().u;
        int v=qu.front().v;
        int w=qu.front().w;
        qu.pop();
        if(a[u][v]==1) continue;
        int p=u+dr[w];
        int q=v+dc[w];
        if(check[p][q]){
            if(d2[p][q][w]>d2[u][v][w]){
                d2[p][q][w]=d2[u][v][w];
                qu.push({p,q,w});
            }
        }
        for(int i=0;i<=3;i++){
            if(i==w) continue;
            int p=u+dr[i];
            int q=v+dc[i];
            if(!check(p,q)) continue;
            if(d2[p][q][i]>d2[u][v][w]+1){
                d2[p][q][i]=d2[u][v][w]+1;
                qu.push({p,q,i});
            }
        }
    }
    int res=ans;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i][j]==1){
                for(int w=0;w<=3;w++){
                    if(res>d1[i][j][w]+d2[i][j][3-w]){
                        res=d1[i][j][w]+d2[i][j][3-w];
                        cnt=1;
                    }
                    else{
                        if(res==d1[i][j][w]+d2[i][j][3-w] && res!=ans){
                            cnt++;
                        }
                    }
                }
            }
        }
    }
    cout<<res<<" ";
    cout<<cnt;
}
