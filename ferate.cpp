#include <bits/stdc++.h>

#define NMAX 100005

using namespace std;

/* n - number of nodes, m - number of edges */
int n, m;
/* source node */
int s;

vector<int> found;
vector<int> low_link;
vector<int> in_stack;
stack<int> st;
vector<int> nodes;
vector<int> visited;

int solution;

/* edges */
vector<int> adj[NMAX];

void tarjan(int node, int &current_start) {
    found[node] = current_start++;
    low_link[node] = found[node];

    /* add node in stack */
    in_stack[node] = 1;
    st.push(node);

    for (int neigh : adj[node]) {
        if (found[neigh] == -1) {
            tarjan(neigh, current_start);

            /* update low_link */
            low_link[node] = min(low_link[node], low_link[neigh]);
        } else {
            if (in_stack[neigh] == 1)
                low_link[node] = min(low_link[node], found[neigh]);
        }
    }

    if (low_link[node] == found[node]) {
        int current = 0;
        nodes.push_back(node);

        while (!st.empty() && current != node) {
            current = st.top();
            st.pop();

            in_stack[current] = 0;
        }
    }
}

void dfs(int node, vector<int>& visited) {
    visited[node] = 1;

    for (auto neigh : adj[node]) {
        if (visited[neigh] == 0)
            dfs(neigh, visited);
    }
}

void solve() {
    int current_start = 0;

    /* get head nodes of scc in topological order */
    for (int i = 1; i <= n; i++) {
        if (found[i] == -1) {
            tarjan(i, current_start);
        }
    }

    /* do dfs from source node */
    dfs(s, visited);

    int n = nodes.size();
    for (int i = n - 1; i >= 0; i--) {
        int node = nodes[i];
        if (node != s && visited[node] == 0) {
            solution++;
            dfs(node, visited);
        }
    }
}

int main() {
    freopen("ferate.in", "r", stdin);
	freopen("ferate.out", "w", stdout);

    cin >> n >> m >> s;

    in_stack = vector<int>(n + 1, 0);
    found = vector<int>(n + 1, -1);
    low_link = vector<int>(n + 1, 0);
    visited = vector<int>(n + 1, 0);

    for (int i = 1; i <= m; i++) {
        int node, neigh;
        cin >> node >> neigh;
        adj[node].push_back(neigh);
    }

    solve();
    cout << solution << "\n";

    return 0;
}
