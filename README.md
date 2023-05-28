Mirza Ana-Maria
321CA

## Homework 2

### Supercomputer
In order to sort the tasks in topological order, I used Khan's algorithm with a
a dequeue. On one side of the dequeue I placed tasks part of a certain set and
on the other end the tasks from the other set. To perform the least amount of
context switches, I retained the last set taken and chose the next task in the
queue based on the set needed.

Complexity: O(|V| + |E|)

### Railroads
For this problem, I used Tarjan's algorithm to find the heads of the conex
components of the graph. Since the nodes are sorted inversly topologically,
I took each head from the tail and made a DFS to mark reacheable nodes,
after marking all nodes reacheble from the source. For each head that
was found unvisited, an edge is added, therefore adding to the solution.

Complexity: O(|V| + |E|)

### Teleportation
This problem I solved using Dijsktra's algorithm with a dp approach. Each node
has associated a distance on a certain period. The edges are relaxed relatively
to their period. The period is calculated using the lowest common multiple of
the input periods of the theleportation tunnels. In order to make the solution
more efficient, I used a min heap structure with insert and delete methods
implemented in O(log n). The code for this functions was taken from Geek for
Geeks. The final solution is found at the end by finding the minumum in the dp
distance vector for the last node.

Complexity: O(|E| * log|V|) 

### Store
For this task I used a dfs to mark the starting and ending time of the nodes.
With the information gained, I could determine if the n-th node could be visited
starting from the source node given.

Complexity: O(|V| + |E|)
