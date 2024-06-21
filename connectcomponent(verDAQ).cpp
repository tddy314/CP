#include<bits/stdc++.h>
#define fi first
#define se second
#define endl "\n"
#define ii pair<int, int>
using namespace std;
const int N = 25e4 + 10;
int lab[N], op[N];
bool ans[N];
stack<pair<int, int> > st;
tuple<int, int, int> query[N];
int root(int v) {
    return lab[v] < 0 ? v : root(lab[v]);
}
void join(int u, int v) {
    if ((u = root(u)) == (v = root(v))) return;
    if (lab[u] > lab[v]) swap(u, v);
    st.push({u, lab[u]});
    st.push({v, lab[v]});
    lab[u] += lab[v];
    lab[v] = u;
}
void rollback(int cnt) {
    while (st.size() > cnt) {
        lab[st.top().fi] = st.top().se;
        st.pop();
    }
}
void solve(int l, int r) {
    if (l == r) {
        auto [t, x, y] = query[l];
        ans[l] = (root(x) == root(y));
        return;
    }
    int mid = l + r >> 1;
    int cur = st.size();
    for(int i = mid + 1; i <= r; i++) {
        auto [t, x, y] = query[i];
        if (t != 2) continue;
        if (op[i] < l) {
            join(x, y);
//            cout << x << " " << y << " " << l << " " << r << endl;
        }
    }
    solve(l, mid);
    rollback(cur);
    for(int i = l; i <= mid; i++) {
        auto [t, x, y] = query[i];
        if (t != 1) continue;
        if (op[i] > r) {
            join(x, y);
//             cout << x << " " << y << " " << l << " " << r << endl;
        }
    }
    solve(mid + 1, r);
    rollback(cur);
}
int main() {
    #define task ""
    cin.tie(0) -> sync_with_stdio(0);
    if (fopen ("task.inp", "r")) {
        freopen ("task.inp", "r", stdin);
        freopen ("task.out", "w", stdout);
    }
    if (fopen (task".inp", "r")) {
        freopen (task".inp", "r", stdin);
        freopen (task".out", "w", stdout);
    }
    int n, Q; cin >> n >> Q;
    map<pair<int, int>, vector<int> > d;
    fill(lab + 1, lab + n + 1, -1);
    for(int i = 1; i <= Q; i++) {
        int t, x, y; cin >> t >> x >> y;
        if (x > y) swap(x, y);
        if (t == 1) {
            d[{x, y}].push_back(i);
            op[i] = Q + 1;
        }
        else if (t == 2) {
            if (d[{x, y}].empty()) {
                op[i] = Q + 1;
                query[i] = {t, x, y};
                continue;
            }
            int j = d[{x, y}].back();
            d[{x, y}].pop_back();
            op[j] = i; op[i] = j;
        }
        query[i] = {t, x, y};
    }
    solve(1, Q);
    for(int i = 1; i <= Q; i++) if (get<0> (query[i]) == 3) {
        cout << ans[i];
    }
}
