/*
    Coded with Leachim's ACM Template.
    No errors. No warnings. ~~
*/
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wunused-const-variable"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#define LL long long
using namespace std;
const int inf=0x3f3f3f3f;
const LL INF=0x3f3f3f3f3f3f3f3f;
const double eps=1e-7;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
const int MOD=998244353;
const int MAXN=2000005;

LL gcd(LL x,LL y) {
    if(!x || !y) return x+y;
    return gcd(y,x%y);
}

/*
    莫队:
    sqrt(m)个块
    块大小n/sqrt(m);
    卡常大小n/sqrt(m*2/3);
*/

struct query {
    int l,r,id;
}q[MAXN];

int a[MAXN],cnt[MAXN];
int block,bl[MAXN];
LL ans1[MAXN],ans2[MAXN],sum;

bool cmp(const query &x, const query &y) {
    if(bl[x.l]!=bl[y.l])
        return bl[x.l]<bl[y.l];
    else if(bl[x.l]&1)
        return x.r<y.r;
    else return x.r>y.r;
}

void modify(int x,int f) {
    sum-=cnt[a[x]]*cnt[a[x]];
    cnt[a[x]]+=f;
    sum+=cnt[a[x]]*cnt[a[x]];
}

void solve() {
    int n,m;
    scanf("%d %d", &n, &m);
    block=n/sqrt(m*2/3);
    for(int i=1;i<=n;i++) {
        scanf("%d", &a[i]);
        bl[i]=(i-1)/block+1;
    }
    for(int i=1;i<=m;i++) {
        scanf("%d %d", &q[i].l, &q[i].r);
        q[i].id=i;
    }
    sort(q+1,q+1+m,cmp);
    memset(cnt+1,0,n*sizeof(cnt[0]));
    sum=0;
    for(int i=1,l=1,r=0;i<=m;i++) {
        for(;r<q[i].r;r++) modify(r+1,1);
        for(;r>q[i].r;r--) modify(r,-1);
        for(;l<q[i].l;l++) modify(l,-1);
        for(;l>q[i].l;l--) modify(l-1,1);
        ans1[q[i].id]=sum-(r-l+1);
        ans2[q[i].id]=1LL*(q[i].r-q[i].l+1)*(q[i].r-q[i].l);
    }
    for(int i=1;i<=m;i++) {
        LL g=gcd(ans1[i],ans2[i]);
        if(!g) printf("0/1\n");
        else printf("%lld/%lld\n", ans1[i]/g, ans2[i]/g);
    }
}

int main() {
    int T=1,cas=1;(void)(cas);
    // scanf("%d", &T);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}