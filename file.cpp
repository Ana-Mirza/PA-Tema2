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

int solution;

/* edges */
vector<int> adj[NMAX];

void tarjan(int node, int &current_start) {
    found[node] = current_start++;
    low_link[node] = found[node];

    /* add node in stack */
    in_stack[node] = 1;
    st.push(node);

    for (int neigh: adj[node]) {
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
        int current;
        nodes.push_back(node);

        while (!st.empty() && current != node) {
            current = st.top();
            st.pop();

            in_stack[current] = 0;
        }
    }
}

void solve() {
    int current_start = 0;

    /* determine number of components disconnected from source node */
    for (int i = 1; i <= n; i++) {
        if (found[i] == -1) {
            tarjan(i, current_start);
        }
    }

    int n = nodes.size();
    // for (int i = n - 1; i >= 0; i--) {
    //     cout << nodes[i] << " ";
    // }
    // cout << "\n";
    // cout << n << " sizeof: " << nodes.size() << "\n";
    for (int i = 0; i < n; i++)
        cout << nodes[i] << " ";
    cout << "\n";
}

int main() {
    cin >> n >> m >> s;

    in_stack = vector<int>(n + 1, 0);
    found = vector<int>(n + 1, -1);
    low_link = vector<int>(n + 1, 0);

    for (int i = 1; i <= m; i++) {
        int node, neigh;
        cin >> node >> neigh;
        adj[node].push_back(neigh);
    }

    solve();

    cout << solution << "\n";

    return 0;
}
