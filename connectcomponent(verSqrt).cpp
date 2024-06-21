#include<bits/stdc++.h>
#define task ""
#define fi first
#define sc second
#define ll long long
#define ld long double
#define rep(i, a, b, c) for (int i = a; i <= b; i += c)
#define ford(i, a, b, c) for (int i = a; i >= b; i -= c)
#define fast ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
using namespace std;
typedef pair<double, double> Tpoint;
typedef pair<int, int> II;
typedef pair<int, II> III;
typedef pair<pair<ll, ll>, ll> LLL;
typedef pair<II, II> IV;
typedef pair<long long, int> LI;
typedef pair<long long, long long> LL;
typedef vector<int> V;
const int inf = 2e9, maxn = 2e5 + 9, mod = 1e9 + 7;
const long long llinf = 1e18;
int n, q, r = 0, par[maxn], Rank[maxn], stblock[500], enblock[500], block[maxn];
int bsize;
III queries[maxn];
struct Edges {
    int tin;
    int tout = q + 1;
    int x, y;
} P[maxn];
map<II, deque<int>> nho;
stack<III> s;

void rollback() {
    while (!s.empty()) {
        III t = s.top();
        s.pop();
        int u = t.fi, p = t.sc.fi, r = t.sc.sc;
        par[u] = p;
        Rank[u] = r;
    }
}

int find(int u) {
    while (u != par[u]) u = par[u];
    return u;
}

void join(int u, int v) {
    u = find(u);
    v = find(v);
    if (Rank[u] < Rank[v]) swap(u, v);
    s.push({u, {par[u], Rank[u]}});
    s.push({v, {par[v], Rank[v]}});
    par[v] = u;

    if (Rank[u] == Rank[v]) ++Rank[u];
}

int main() {
    if (fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    fast;
    cin >> n >> q;

    rep(i, 1, q, 1) {
        int typ, u, v;
        cin >> typ >> u >> v;
        if (u > v) swap(u, v);

        queries[i] = {typ, {u, v}};
        if (queries[i].fi == 1) {
            ++r;
            nho[II(u, v)].push_back(r);
            P[r] = {i, q + 1, u, v};
        }
        else if (queries[i].fi == 2) {
            if (nho[II(u, v)].empty()) continue;
            int x = nho[II(u, v)].front();
            nho[II(u, v)].pop_front();
            P[x].tout = i;
        }
    }

    bsize = sqrt(q);

    rep(i, 1, q, 1) block[i] = (i - 1)/bsize + 1;

    rep(i, 1, q, 1) enblock[block[i]] = max(enblock[block[i]], i);


    vector<IV> A;

    rep(i, 1, q, 1) {
        if (block[i] != block[i - 1]) {
            A.clear();
            rep(u, 1, n, 1) par[u] = u, Rank[u] = 1;
            int L = i, R = enblock[block[i]];
            rep(j, 1, r, 1) {
                int tin = P[j].tin, tout = P[j].tout, u = P[j].x, v = P[j].y;
                if (tin <= L && R <= tout) join(u, v);
                else if (tin < R || L < tout) A.push_back({{tin, tout}, {u, v}});
            }

            while (!s.empty()) s.pop();
        }
        if (queries[i].fi == 3) {
            for (IV x : A) {
                int tin = x.fi.fi, tout = x.fi.sc, u = x.sc.fi, v = x.sc.sc;
                if (tin <= i && i <= tout) join(u, v);
            }
            int u = queries[i].sc.fi, v = queries[i].sc.sc;
            cout << (find(u) == find(v));
            rollback();
        }
    }
}
