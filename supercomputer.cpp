#include <bits/stdc++.h>

#define NMAX 100005

using namespace std;

/* n = number of nodes; m = number of edges */
int n, m;

/* adjacency array */
vector<int> adj[NMAX];
/* array for indegree of each node */
vector<int> indegree(NMAX, 0);
/* array storing data set for each node */
vector<int> dataSet(NMAX, 0);

int lastSet;

int solve(int set) {
    deque<int> deq;
    int changes = 0;

    /* find indegree of nodes */
    for (int i = 1; i <= n; i++) {
        for (int neigh: adj[i]) {
            indegree[neigh]++;
        }
    }

    /* add in dequeue all vertices with indegree 0 */
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            if (dataSet[i] == 1)
                deq.push_front(i);
            else
                deq.push_back(i);
        }
    }

    lastSet = set;

    /* khan with dequeue */
    while(!deq.empty()) {
        int node = (lastSet == 1) ? deq.front() : deq.back();
        (lastSet == 1) ? deq.pop_front() : deq.pop_back();

        /* increase number of changes if necessary */
        if (dataSet[node] != lastSet) {
            lastSet = dataSet[node];
            changes++;
        }

        /* add all neighbors with indegree 0 */
        for (int neigh: adj[node]) {
            indegree[neigh]--;

            if (indegree[neigh] == 0) {
                if (dataSet[neigh] == 1)
                    deq.push_front(neigh);
                else
                    deq.push_back(neigh);
            }
        }
    }
    return changes;
}

int main() {
    freopen("supercomputer.in", "r", stdin);
	freopen("supercomputer.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> dataSet[i];

    /* read m edges */
    for (int i = 1; i <= m; i++) {
        int node, neigh;
        cin >> node >> neigh;
        adj[node].push_back(neigh);
    }

    int sol = min(solve(1), solve(2));
    cout << sol << "\n";
    return 0;
}
