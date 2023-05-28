#include <bits/stdc++.h>

using namespace std;

#define NMAX 10000
#define INF 1 << 31

int mod;
int n, m, k;
uint64_t solution;

/* adjacency array */
vector<pair<int, int>> adj[NMAX];
vector<pair<int, int>> teleport[NMAX];
uint64_t dist[NMAX][NMAX];

void solve() {
    /* initilize dist matrix */
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= mod; j++)
            dist[i][j] = INF;
    }

    /* apply Dijskra starting from source node = 1 */
    auto cmp = [](tuple<int, uint64_t, int> left,
                  tuple<int, uint64_t, int> right) {
        auto [x, y, z] = left;
        auto [a, b, c] = right;
        return y > b; };
        priority_queue<tuple<int, uint64_t, int>,
                             vector<tuple<int, uint64_t, int>>,
                             decltype(cmp)> pq(cmp);

    int source = 1;
    dist[source][0] = 0;
    pq.push({source, dist[source][0], 0});

    /* start relaxation loop */
    while (!pq.empty()) {
        auto [node, distance, mode] = pq.top();
        pq.pop();

        /* relax all normal edges */
        for (pair<int, int> neigh : adj[node]) {
            uint64_t seconds = neigh.second;
            int new_mode = (mode + seconds) % mod;
            uint64_t new_dist = distance + seconds;
            if (new_dist < dist[neigh.first][new_mode]) {
                dist[neigh.first][new_mode] = new_dist;
                if (neigh.first != n)
                    pq.push({neigh.first, new_dist, new_mode});
            }
        }

        /* relax teleportation edges */
        for (pair<int, int> neigh : teleport[node]) {
            /* check if teleportation can be used */
            int period = neigh.second;
            if (mode % period != 0)
                continue;

            int new_mode = (mode + 1) % mod;
            uint64_t new_dist = distance + 1;
            if (new_dist < dist[neigh.first][new_mode]) {
                dist[neigh.first][new_mode] = new_dist;

                if (neigh.first != n)
                    pq.push({neigh.first, new_dist, new_mode});
            }
        }
    }

    /* find smallest possible solution */
    solution = INF;
    for (int i = 0; i < mod; i++) {
        if (solution > dist[n][i])
            solution = dist[n][i];
    }
}

int main() {
    freopen("teleportare.in", "r", stdin);
	freopen("teleportare.out", "w", stdout);

    ios_base::sync_with_stdio(false);

    scanf("%d%d%d", &n, &m, &k);

    /* read normal roads */
    for (int i = 1; i <= m; i++) {
        int node, neigh, weigh;
        scanf("%d%d%d", &node, &neigh, &weigh);
        adj[node].push_back({neigh, weigh});
        adj[neigh].push_back({node, weigh});
    }

    /* read teleportation tunnels */
    int multiple = 1;
    for (int i = 1; i <= k; i++) {
        int node, neigh, period;
        scanf("%d%d%d", &node, &neigh, &period);
        multiple = lcm(multiple, period);
        teleport[node].push_back({neigh, period});
        teleport[neigh].push_back({node, period});
    }
    mod = multiple;

    solve();
    printf("%ld\n", solution);
    return 0;
}
