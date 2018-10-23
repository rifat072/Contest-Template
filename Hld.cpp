///https://www.spoj.com/problems/QTREE/
#include<bits/stdc++.h>
#define mx 10004
using namespace std;
typedef long long ll;
const int inf=1000000000;
const int M=10000003;

int n,ptr,chainno;
vector<int> adj[mx];
vector<int> cost[mx];
int par[mx];
int chainid[mx];
int chainhead[mx];
int base[mx];
int posbase[mx];
int level[mx];
int sparse[mx][15];
int tree[6*mx];
int subsize[mx];
pair<int,int> p[mx];

inline void aintclear(){
for(int i=0;i<=mx;i++){
    adj[i].clear();
    cost[i].clear();
    par[i]=-1;
    chainid[i]=-1;
    chainhead[i]=-1;
    base[i]=0;
    level[i]=0;
    posbase[i]=-1;
    subsize[i]=0;
    posbase[i]=-1;
}
memset(sparse,-1,sizeof(sparse));
ptr=1;
chainno=1;
}
inline int left(int nd){return nd<<1;}
inline int right(int nd){return (nd<<1)|1;}
inline int mid(int b,int e){return (b+e)>>1;}


void dfs(int u,int depth)
{
sparse[u][0]=par[u];
level[u]=depth;
subsize[u]=1;
for(int i=0;i<adj[u].size();i++){
    int v=adj[u][i];
    if(v!=par[u]){
        par[v]=u;
        dfs(v,depth+1);
        subsize[u]+=subsize[v];
    }
}
}

inline void lca_init(){
for(int j=1;(1<<j)<=n;j++){
    for(int i=1;i<=n;i++){
        if(sparse[i][j-1]!=-1)sparse[i][j]=sparse[sparse[i][j-1]][j-1];
    }
}
}

void hld(int cur,int cst){
if(chainhead[chainno]==-1) chainhead[chainno]=cur;

chainid[cur]=chainno;
posbase[cur]=ptr;
base[ptr]=cst;
ptr++;

int m=-inf;
int sc=-1;
for(int i =0;i<adj[cur].size();i++){
    int v=adj[cur][i];
    if(v!=par[cur] and (sc==-1 or subsize[sc]<subsize[v])){
        sc=v;
        m=cost[cur][i];
    }
}

if(sc!=-1){
    hld(sc,m);
}

for(int i=0;i<adj[cur].size();i++){
    int v=adj[cur][i];
    if(v!=sc and v!=par[cur]){
        chainno++;
        hld(v,cost[cur][i]);
    }
}

}

void build(int nd,int b,int e){
if(b==e){
    tree[nd]=base[b];
    return;
}
build(left(nd),b,mid(b,e));
build(right(nd),mid(b,e)+1,e);
tree[nd]=tree[left(nd)]>tree[right(nd)]?tree[left(nd)]:tree[right(nd)];
}

int query_tree(int nd,int b,int e,int i,int j){
if(b>e) return -inf ;
if(i>e or j<b) return -inf;
if(i<=b and j>=e) return tree[nd];
ll ret1=query_tree(left(nd),b,mid(b,e),i,j);
ll ret2=query_tree(right(nd),mid(b,e)+1,e,i,j);
return ret1>ret2? ret1: ret2;
}
void update_tree(int nd,int b,int e,int i,int v){
if(b>e) return;
if(i>e or i<b) return;
if(b==e and b==i){
    tree[nd]=v;
    return;
}
update_tree(left(nd),b,mid(b,e),i,v);
update_tree(right(nd),mid(b,e)+1,e,i,v);
tree[nd]=tree[left(nd)]>tree[right(nd)]?tree[left(nd)]:tree[right(nd)];
}

inline int query_lca(int p,int q){
if(level[p]<level[q])swap(p,q);
int log=0;
while((1<<log)<=level[p])log++;
log--;
for(int i=log;i>=0;i--){
    if(level[p]-(1<<i)>=level[q]){
        p=sparse[p][i];
    }
}
if(p==q) return p;
for(int i=log;i>=0;i--){
    if(sparse[p][i]!=-1 and sparse[p][i]!=sparse[q][i]){
        p=sparse[p][i];
        q=sparse[q][i];
    }
}
return par[p];
}

inline int query_up(int u,int v){
if(v==u) return 0;
int vchain=chainid[v];
int uchain;
int ret=-inf;
while(1){
    uchain=chainid[u];
    if(uchain==vchain){
        if(v==u) break;
        ll ret1= query_tree(1,1,ptr,posbase[v]+1,posbase[u]);
        ret=ret>ret1 ? ret:ret1;
        break;
    }
    ll ret2=query_tree(1,1,ptr,posbase[chainhead[uchain]],posbase[u]);
    ret=ret>ret2? ret:ret2;
    u=chainhead[uchain];
    u=par[u];
}
return ret;
}

inline int query(int u,int v){
int lca=query_lca(u,v);
ll ret1=query_up(u,lca);
ll ret2=query_up(v,lca);
return ret1>ret2? ret1:ret2;
}
inline void change(int i,int c){
int in;
int u=p[i].first;
int v=p[i].second;
if(par[v]==u)in=v;
else in=u;
update_tree(1,1,ptr,posbase[in],c);
}
int main()
{
//freopen("input.txt","r",stdin);
int t;

scanf("%d",&t);
while(t--){
    aintclear();
    scanf("%d",&n);
    for(int i=0;i<n-1;i++){
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        adj[u].push_back(v);
        cost[u].push_back(c);
        adj[v].push_back(u);
        cost[v].push_back(c);
        p[i+1]=make_pair(u,v);
    }
    dfs(1,1);
    lca_init();
    hld(1,-1);
    build(1,1,ptr);
    char str[100];
    while(scanf("%s",str)){
        if(str[0]=='D') break;
        else if(str[0]=='Q'){
            int u,v;
            scanf("%d%d",&u,&v);
            printf("%d\n",query(u,v));
        }
        else{
            int i,c;
            scanf("%d%d",&i,&c);
            change(i,c);
        }
    }
    //printf("\n");
}

return 0;
}

