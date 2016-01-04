#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

struct edge
{
    int a, b, id;
};
const int maxn = 1e5;
const int maxm = 3*maxn-6;

int n, m;
edge es[maxm];
vector<pair<int, int>> g[maxn];
bool was[maxn];
bool vp[maxn];
bool ep[maxm];

void cw(int q = n)
{
    fill(was, was+q, 0);
}

vector<vector<int>> fs;

int dfs1(int v, int prev)
{
    was[v] = 1;
    for (auto &e: g[v]) {
        const int t = e.first;
        if (t == prev) {
            continue;
        }
        if (was[t]) {
            fs[0].push_back(e.second);
            return t;
        } else {
            int q;
            q = dfs1(t, v);
            if (q >= 0) {
                fs[0].push_back(e.second);
                return (v == q ? -2 : q);
            } else if (q == -2) {
                return -2;
            }
        }
    }
    return -1;
}

void dfs2(int v)
{
    was[v] = 1;
    for (auto &e: g[v]) {

    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    assert(m <= 3*n-6);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
        es[i] = {a, b, i};
    }
    fs.push_back({});
    cw();
    assert(dfs1(0, -1) == -2);
    for (auto &e: fs[0]) {
        cout << e << ' ';
        ep[e] = 1;
        vp[es[e].a] = 1;
        vp[es[e].b] = 1;
    }
    fs.push_back({});
    fs[1] = fs[0];
    reverse(fs[1].begin(), fs[1].end());
    return 0;
}
