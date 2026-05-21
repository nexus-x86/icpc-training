// https://dmoj.ca/problem/ccc16s3

#include <iostream>
#include <vector>

using namespace std;

const int mx = 1e5 + 1;
int n, m;
vector<int> adjList[mx];
int pho[mx];

int diam = 0;
int far = -1;

// We use DFS to prune all nodes that are not a part of the vertex-induced
// subgraph formed by the Pho restaurants. This is a fancy way of saying, we
// ignore a node if it doesn't lead to a Pho restaurant. The function returns
// 1 if a node is in that subgraph and returns 0 otherwise. 
int dfs(int cur, int prev) {
    for (int child : adjList[cur]) {
        if (child != prev && dfs(child, cur)) {
            pho[cur] = 1; 
        }
    }
    if (pho[cur]) {
        return 1;
    }
    n -= 1;
    return 0;
}

// This function gets the diameter of the subgraph. We must call it twice.
void dfs2(int cur, int prev, int dist) {
    if (dist > diam) {
        diam = dist;
        far = cur;
    }
    for (int child : adjList[cur]) {
        if (child != prev && pho[child]) {
            dfs2(child, cur, dist + 1);
        }
    }
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    int a, b, c;
    for (int i = 0; i < m; i++) {
        cin >> a;
        pho[a] = 1;
    }
    for (int i = 0; i < n - 1; i++) {
        cin >> c >> b;
        adjList[c].push_back(b);
        adjList[b].push_back(c);
    }
    // We know a is a Pho restaurant and therefore is on the path that must be
    // traversed.
    dfs(a, -1);
    diam = 0;
    dfs2(a, -1, 0);
    diam = 0;
    dfs2(far, -1, 0);

    // We have the subgraph and we want to minimize our time visiting each leaf.
    // We notice that if we navigate the tree visting each node once and then
    // return to our starting position. This will always take 2 * (n - 1) steps
    // However we don't need to do this in the actual problem. There exists an
    // edge where we only traverse once. To minimize the visit we maximize this
    // edge which turns out to be the graph's diameter. We use standard DFS to
    // find the diameter. 
    cout << 2 * (n - 1) - diam << "\n";
}