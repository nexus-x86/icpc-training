// https://dmoj.ca/problem/ccc21s4

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

const int mx = 2e5 + 2;
const ll INF = 1e18;
vector<ll> adjList[mx];
ll dist[mx];
ll order[mx];
ll N, W, D;

ll seg[4 * mx];

void build(ll node, ll l, ll r) {
    if (l == r) {
        if (dist[order[l]] == INF) {
            seg[node] = INF;
        } else {
            seg[node] = l - 1 + dist[order[l]];
        }
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    seg[node] = min(seg[node * 2], seg[node * 2 + 1]);
}

void update(ll node, ll l, ll r, ll pos) {
    if (l == r) {
        if (dist[order[l]] == INF) {
            seg[node] = INF;
        } else {
            seg[node] = l - 1 + dist[order[l]];
        }
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        update(2 * node, l, mid, pos);
    } else {
        update(2 * node + 1, mid + 1, r, pos);
    }
    seg[node] = min(seg[node * 2], seg[node * 2 + 1]);
}

void dijkstra() {
    for (int i = 1; i <= N; i++) {
        dist[i] = INF;
    }
    dist[N] = 0;
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, N});
    while (!pq.empty()) {
        pll a = pq.top();
        ll d = a.first;
        ll v = a.second;
        pq.pop();

        if (d > dist[v]) {
            continue;
        }
        for (ll u: adjList[v]) {
            if (dist[v] + 1 < dist[u]) {
                dist[u] = dist[v] + 1;
                pq.push({dist[u], u});
            }
        }
    }
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> W >> D;

    for (int i = 0; i < W; i++) {
        ll a, b;
        cin >> a >> b;
        adjList[b].push_back(a); // edge reversal
    }

    for (int i = 1; i <= N; i++) {
        cin >> order[i];
    }

    

    // We compute once the minimum distance from N to every node.
    dijkstra();

    build(1, 1, N);

    for (int i = 0; i < D; i++) {
        ll x, y;
        cin >> x >> y;
        ll temp = order[x];
        order[x] = order[y];
        order[y] = temp;

        update(1, 1, N, x);
        update(1, 1, N, y);

        cout << seg[1] << "\n";
        
        // f(j) = (j - 1) + dist[order[j]]
        // we want the minimum of f(j) for all j in 1 to n
        // point updates + global min query

        // ll ans = INF;
        // for (int j = 1; j <= N; j++) {
        //     if (dist[order[j]] < INF) {
        //         ans = min(ans, (ll)(j - 1) + dist[order[j]]);
        //     }
        // }
        // cout << ans << "\n";
    }
}