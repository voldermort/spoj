#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define M 100
#define N 100200
vector<int> A[N];
typedef pair<pair<int,int>,int> PI3;
vector<PI3> P;
#define xx first.first
#define yy first.second
#define zz second
#define MP make_pair
int PP[100000];
int Next[M],Ans[M];
bool V[M];
int m,n;
int Q[N],Pr[N],D[N];
void bfs(int x)
{
    memset(Pr,0,sizeof Pr);
    int L=1,R=1;
    Q[1]=x;
    while(L<=R)
    {
        for(vector<int>::iterator I=A[Q[L]].begin();I!=A[Q[L]].end();I++)
            if(*I!=Pr[Q[L]])
                Q[++R]=*I,Pr[*I]=Q[L];
        L++;
    }
}
int sz[N],ch[N],hh[N];
inline bool cmp(int x,int y){return hh[x]<hh[y];}
int HT(int H)
{
    bfs(H);
    for(int cc=n;cc>=1;cc--)
    {
        int u=Q[cc];
        sz[u]=1;
        int cn=0;
        for(vector<int>::iterator e=A[u].begin();e!=A[u].end();e++)
        {
            int v=*e;
            if(v==Pr[u])
                continue;
            ch[cn++]=v;
            sz[u]+=sz[v];
        }
        sort(ch,ch+cn,cmp);
        int r=sz[u];
        for(int cc=0;cc<cn;cc++)
        {
            if(!cc)
                r*=PP[1];
            else
                r*=PP[sz[ch[cc-1]]];
            r+=hh[ch[cc]];
        }
        hh[u]=r;
    }
    return hh[H];
}
int main()
{
    PP[0]=1;
    for(int i=1;i<100000;i++)
        PP[i]=PP[i-1]*1000000007;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        m=2;
        scanf("%d",&n);
        P.clear();
        for(int mm=1;mm<=m;mm++)
        {
            for(int i=1;i<=n;i++)
                A[i].clear();
            for(int i=2,x,y;i<=n;i++)
            {
                scanf("%d%d",&x,&y);
                A[x].push_back(y),A[y].push_back(x);
            }
            bfs(1);
            int u=Q[n];
            bfs(u);
            int v=Q[n];
            int C=0;
            while(v!=0)
            {
                D[++C]=v;
                v=Pr[v];
            }
            int x=0,y=0;
            if(C&1)
                x=y=D[(C+1)/2];
            else
                x=D[C/2],y=D[C/2+1];
            int hx,hy;
            if(x==y)
                hx=hy=HT(x);
            else
                hx=HT(x),hy=HT(y);
            if(hx>hy)
                swap(hx,hy);
            P.push_back(MP(MP(hx,hy),mm));
        }
        sort(P.begin(),P.end());
        if(P[0].first==P[1].first)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}

