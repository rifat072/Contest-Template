//LightOJ - 1251
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mx=200005;
const ll inf=1000000000000000;
ll n,t;

vector<ll> adj[mx];
stack<ll> stk;

ll scccnt=0;
ll sccnum[mx];
ll st[mx];
ll low[mx];
bool visited[mx];
bool instk[mx];

void clear(){
    t=0;
    scccnt=0;
    for(ll i=0;i<mx;i++){
        adj[i].clear();
        visited[i]=false;
        instk[i]=false;
        sccnum[i]=-1;
        st[i]=-1;
        low[i]=inf;
    }
    while(!stk.empty())stk.pop();
}

void tarjan(ll u,ll p){
    visited[u]=true;
    st[u]=low[u]=++t;
    stk.push(u);
    instk[u]=true;
    for(ll i=0;i<(ll)adj[u].size();i++){
        ll v=adj[u][i];
        if(visited[v]==false){
            tarjan(v,u);
        }
        if(instk[v]==true)low[u]=min(low[u],low[v]);

    }
    if(low[u]==st[u]){
        ++scccnt;
        while(1){
            ll v=stk.top();stk.pop();
            sccnum[v]=scccnt;
            instk[v]=false;
            if(v==u)break;
        }
    }
}

void findscc(){
    for(ll i=0;i<2*n;i++){
        if(visited[i]==false){
            tarjan(i,-1);
        }
    }
}

void addedge(ll u,ll v){
        }
void print(){
    for(ll i=0;i<2*n;i++){
        cout<<i<<' '<<sccnum[i]<<' '<<endl;

    }
}

ll convert(ll n){
    ll x=abs(n);
    x--;
    x*=2;
    if(n<0)x++;
    return x;
}

void orclause(ll u,ll v){
    //cout<<convert(-u)<<' '<<convert(v)<<endl;
    //cout<<convert(-v)<<' '<<convert(u)<<endl;
    adj[convert(-u)].push_back(convert(v));
    adj[convert(-v)].push_back(convert(u));
}

bool possible(){
    for(ll i=1;i<=n;i++){
        ll a=convert(i);
        ll b=a+1;
        if(sccnum[a]==sccnum[b] and sccnum[a]!=-1)return false;
    }
    return true;
}

int main(){
    //freopen("input.txt","r",stdin);
    ll t;
    scanf("%lld",&t);
    for(ll ts=1;ts<=t;ts++){
        clear();
        ll m;
        scanf("%lld %lld",&m,&n);
        while(m--){
            ll u,v;
            scanf("%lld %lld",&u,&v);
            orclause(u,v);
        }
        findscc();
        //cout<<scccnt<<endl;
        //print();
        bool ps=possible();
        printf("Case %lld: ",ts);
        if(ps){
            printf("Yes\n");
            vector<ll> v;
            for(ll i=1;i<=n;i++){
                ll a=convert(i);
                ll b=a+1;
                if(sccnum[a]<sccnum[b]){
                    v.push_back(i);
                }
                else{
                   // v.push_back(-i);
                }
            }
            sort(v.begin(),v.end());
            printf("%lld",(ll)v.size());
            for(ll i=0;i<(ll)v.size();i++){
                printf(" %lld",v[i]);
            }
            printf("\n");


        }
        else{
            printf("No\n");
        }


    }

    return 0;

}
