#include <bits/stdc++.h>

#define NMAX 100005

using namespace std;

int d, e, q, n;
int timestamp;

/* adjacency matrix */
vector<int> adj[NMAX];
/* array of pairs of questions */
vector<pair<int, int>> pairs;

/* opposite array of start array keeping timestamp as index */
vector<int> timest(5 * NMAX, -1);
/* array for nodes starting time */
vector<int> start(5 * NMAX, -1);
/* array for nodes end time */
vector<int> fin(5 * NMAX, -1);

void dfs(int node, vector<int>& visited) {
    visited[node] = 1;

    /* mark start time */
    start[node] = ++timestamp;
    timest[timestamp] = node;

    for (auto neigh : adj[node]) {
        if (visited[neigh] == 0)
            dfs(neigh, visited);
    }

    /* mark end time */
    fin[node] = timestamp;
}

void solve() {
    freopen("magazin.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    vector<int> visited(n + 1, 0);

    /* initalization */
    timestamp = -1;

    /* make a dfs and save start time and end time for each node */
    dfs(1, visited);

    for (pair<int, int> question : pairs) {
        int startNode = question.first;
        int dist = question.second;
        int finalNode = timest[start[startNode] + dist];

        /* check if final node can be reached from start node */
        if (finalNode != -1 && start[finalNode] <= fin[startNode]) {
            cout << finalNode << "\n";
        } else {
            cout << -1 << "\n";
        }
    }
}

int main() {
    freopen("magazin.in", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin >> n >> q;

    /* read input edges */
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        adj[x].push_back(i + 1);
    }

    /* read input questions */
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        pair<int, int> p;
        pairs.push_back({x, y});
    }

    solve();
    return 0;
}
