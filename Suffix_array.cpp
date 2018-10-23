///UVALive - 2755
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mx=100005;

const ll maxn = 200010;

int n, n1;
string T;
int RA[maxn], tempRA[maxn];
int SA[maxn], tempSA[maxn];
int c[maxn];
int PLCP[maxn], LCP[maxn];
int Phi[maxn];

void coutingSort(int k){
    int sum , maxi = max(300,n);
    memset(c, 0, sizeof c);
    for(int i = 0; i < n; i++){
        c[i+k<n? RA[i+k] : 0]++;
    }
    for(int i = sum =  0; i < maxi; i++){
        int t = c[i];
        c[i] = sum;
        sum += t;
    }

    for(int i = 0; i < n; i++){
        tempSA[c[SA[i]+k<n? RA[SA[i]+k]:0]++] = SA[i];
    }
    for(int i = 0; i < n; i++){
        SA[i] = tempSA[i];
    }

}

void constractSA(){
    int r;
    for(int i = 0; i < n; i++) RA[i] = T[i];
    for(int i = 0; i < n; i++) SA[i] = i;
    for(int k = 1; k < n; k <<=1){
        coutingSort(k);
        coutingSort(0);
        tempRA[SA[0]] = r = 0;
        for(int i = 1; i < n; i++){
            tempRA[SA[i]] = ( RA[SA[i-1]] == RA[SA[i]] and RA[SA[i-1]+k] == RA[SA[i]+k] ) ? r : ++r;
        }
        for(int i = 0; i < n; i++){
            RA[i] = tempRA[i];
        }

        if(RA[SA[n-1]] == n-1) break;
    }
}

void computeLCP(){
    int L;
    Phi[SA[0]] = -1;
    for(int i = 1; i< n; i++) Phi[SA[i]] = SA[i-1];
    for(int i = L = 0; i < n; i++){
        if(Phi[i] == -1){
            PLCP[i] = 0;
            continue;
        }
        while(T[i+L] == T[Phi[i]+L])L++;
        PLCP[i] = L;
        L = max(0,L-1);
    }
    for(int i = 0; i< n; i++){
        LCP[i] = PLCP[SA[i]];
    }

}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        cin>>n1>>T;
        T += T;
        T += '$';
        n = T.size();
        constractSA();
        computeLCP();
        n1++;
        for(int i = 0; i < n; i++){
            int len = n - SA[i];
            if(len >= n1){
                int ans = SA[i];
                int j = i + 1;
                while(j < n){
                    if(LCP[j] < n1) break;
                    ans = min(ans,SA[j]);
                    j++;
                }
                printf("%d\n",ans);
                //cout<<T.substr(ans,n1-1)<<endl;
                break;
            }
        }
    }   
}
