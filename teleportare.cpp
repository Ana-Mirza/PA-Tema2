#include <bits/stdc++.h>
#include <numeric>

using namespace std;

#define NMAX 10005
#define INF 1 << 31

int my_lcm;
int n, m, k;
uint64_t solution;

/* adjacency arrays */
vector<pair<int, int>> adj[NMAX];
vector<pair<int, int>> teleport[NMAX];

uint64_t dist[NMAX][NMAX];

/* structure for a node */
struct Node {
    int node;
    uint64_t distance;
    int mode;

    Node(int _node1, uint64_t _distance1, int _mode1)
        : node(_node1)
        , distance(_distance1)
        , mode(_mode1) { }
};

/* structure for min heap */
struct Min_Heap {
    /* mean heap vector */
    vector<Node> min_heap;

    /* insert in heap */
    void insert(Node node) {
        min_heap.push_back(node);
        int index = min_heap.size() - 1;;

        while (index > 0) {
            int index2 = ((index - 1) >> 1);
            Node node1 = min_heap[index2];
            Node node2 = min_heap[index];
            if (node1.distance < node2.distance)
                break;

            swap(min_heap[index], min_heap[((index - 1) >> 1)]);
            index = ((index - 1) >> 1);
        }
    }

    /* remove from heap first element */
    void delete_first() {
        Node lastNode = min_heap.back();

        int index = 0;
        int min_heap_size = min_heap.size();

        min_heap[index] = min_heap[min_heap_size - 1];
        min_heap.pop_back();

        /* if heap is empty stop heapify */
        if (min_heap.empty()) {
            return;
        }

        /* rebalance min heap */
        while (true) {
            int left_child = (index << 1) + 1;
            int right_child = (index << 1) + 2;
            int smallest = index;
            if (left_child < min_heap_size) {
                Node node1 = min_heap[left_child];
                Node node2 = min_heap[smallest];

                if (node1.distance < node2.distance)
                    smallest = left_child;
            }
            if (right_child < min_heap_size) {
                Node node1 =  min_heap[right_child];
                Node node2 = min_heap[smallest];

                if (node1.distance < node2.distance)
                smallest = right_child;
            }
            if (smallest != index) {
                swap(min_heap[index], min_heap[smallest]);

                index = smallest;
            } else {
                break;
            }
        }

        min_heap[index] = lastNode;
    }
};

/* lowest common multiple */
long long lcm(long long a, long long b) {
    if (a > b)
        return (a / gcd(a, b)) * b;
    else
        return (b / gcd(a, b)) * a;
}

void solve() {
    /* initilize dist matrix */
    solution = INF;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= my_lcm; j++)
            dist[i][j] = INF;
    }

    Min_Heap heap;

    int source = 1;
    dist[source][0] = 0;
    heap.insert(Node(source, 0, 0));

    /* start relaxation loop */
    while (!heap.min_heap.empty()) {
        Node current = heap.min_heap[0];
        heap.delete_first();

        int node = current.node;
        uint64_t distance = current.distance;
        int mode = current.mode;

        /* stop if got to destination */
        if (node == n)
            break;

        /* relax teleportation edges */
        for (pair<int, int> neigh : teleport[node]) {
            /* check if teleportation can be used */
            int period = neigh.second;
            if (distance % period == 0) {
                int new_mode = (mode + 1) % my_lcm;
                uint64_t new_dist = distance + 1;
                if (new_dist < dist[neigh.first][new_mode]) {
                    dist[neigh.first][new_mode] = new_dist;

                    heap.insert(Node(neigh.first, new_dist, new_mode));
                }
            }
        }

        /* relax all normal edges */
        for (pair<int, int> neigh : adj[node]) {
            uint64_t seconds = neigh.second;
            int new_mode = (mode + seconds) % my_lcm;
            uint64_t new_dist = distance + seconds;

            if (new_dist < dist[neigh.first][new_mode]) {
                dist[neigh.first][new_mode] = new_dist;

                heap.insert(Node(neigh.first, new_dist, new_mode));
            }
        }
    }

    solution = INF;
    for (int i = 0; i < my_lcm; i++)
        solution = min(solution, dist[n][i]);
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

        if (multiple % period != 0)
            multiple = lcm(multiple, period);
        teleport[node].push_back({neigh, period});
        teleport[neigh].push_back({node, period});
    }
    my_lcm = multiple;

    solve();
    printf("%ld\n", solution);
    return 0;
}
