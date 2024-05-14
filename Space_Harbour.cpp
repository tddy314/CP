
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 300003;

int64_t it[4*maxn];

void upd(int r,int k,int l,int u,int64_t val)
{
    if(k==l)
    {
        it[r]=val;
        return;
    }

    int g = (k+l)/2;
    if(u<=g) upd(2*r,k,g,u,val);
    else upd(2*r+1,g+1,l,u,val);
    it[r] = it[2*r]+it[2*r+1];
}

int64_t get(int r,int k,int l,int u,int v)
{
    if(u>v) return 0;
    if(v<k||u>l) return 0;
    if(u<=k&&l<=v) return it[r];
    int g = (k+l)/2;
    return get(2*r,k,g,u,v)+get(2*r+1,g+1,l,u,v);
}

int n,m,q;
int x[maxn],v[maxn];
int a[maxn];
set<int> har;

void add(int i,int val)
{
    int j;
    a[i]=val;
    har.insert(i);
    auto it = har.lower_bound(i);
    if(it!=har.begin())
    {
        it--;
        j = *it;
        int64_t val_upd = 1ll*(i-1-j+1)*(i-j-1)/2;
        upd(1,1,n,j,1ll*a[j]*val_upd);
        it++;
    }
    it++;
    if(it!=har.end())
    {
        j = *it;
        int64_t val_upd = 1ll*(j-i+1-1)*(j-i-1)/2;
        upd(1,1,n,i,1ll*a[i]*val_upd);
    }
}

void input()
{
    cin>>n>>m>>q;

    for(int i=1; i<=m; i++)
        cin>>x[i];
    for(int i=1; i<=m; i++)
        cin>>v[i];

    for(int i=1; i<=m; i++)
        add(x[i],v[i]);
}

int64_t query(int l,int r)
{
    int x,y;
    auto it1 = har.upper_bound(l);
    auto it2 = har.upper_bound(r);
    it1--;
    it2--;
    x=*it1;
    y=*it2;
    it1++;
    it2++;
    int mid = *it1;
    int64_t ans = 0;

    if(x==y)
    {
        if(l==x) l++;
        ans = 1ll*(r-l+1)*(mid)-1ll*(r+l)*(r-l+1)/2;
        ans = ans*a[x];
        return ans;
    }


    if(l==x) ++l;

    ans += (1ll*(mid-l)*mid-1ll*(mid-1+l)*(mid-l)/2)*a[x];

    ans +=  get(1,1,n,mid,y);

    if(r!=n)
    {
        r++;
        mid = *it2;
        ans -= (1ll*(mid-r)*mid -1ll*(mid-1+r)*(mid-r)/2)*a[y];
    }

    return ans;

}

void output()
{
    int t,l,r;
    for(int i=1; i<=q; i++)
    {
        cin>>t>>l>>r;
        if(t==1)
            add(l,r);
        else
            cout<<query(l,r)<<"\n";
    }
}

void progress()
{
    input();
    output();
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int numbers_of_test=1;
    //cin>>numbers_of_test;
    while(numbers_of_test--)
        progress();
}

