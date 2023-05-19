#include <bits/stdc++.h>

#define NMAX 100005

using namespace std;

int n, m;
vector<int> adj[NMAX];

int solve() {

    /* khan with dequeue */

    return 0;
}

int main() {
    freopen("feribot.in", "r", stdin);
	freopen("feribot.out", "w", stdout);

    cin >> n >> m;

    /* read data set needed for task i */
    vector<long long> data_set(n + 1, 0);

    for (int i = 1; i <= n; i++)
        cin >> data_set[i];

    /* read m edges */
    for (int i = 1; i <= m; i++) {
        int node, neigh;
        cin >> node >> neigh;
        adj[node].push_back(neigh);
    }

    int solution = solve();

    cout << solution << "\n";
    return 0;
}
