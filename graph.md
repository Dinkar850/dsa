## Snippets

```cpp
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
priority_queue<vector<int>,c vector<vector<int>>, greater<vector<int>>> pq;
```

```cpp
class DisjointSet {
    vector<int> parent, size, rank;
    public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        size.resize(n + 1, 1);
        parent.resize(n + 1);
        for(int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    int findParent(int node) {
        if(parent[node] == node) {
            return node;
        }
        return parent[node] = findParent(parent[node]);
    }

    void unionByRank(int node1, int node2) {
        int up_node1 = findParent(node1);
        int up_node2 = findParent(node2);
        if(rank[up_node1] < rank[up_node2]) {
            parent[up_node1] = up_node2;
        } else if(rank[up_node1] > rank[up_node2]) {
            parent[up_node2] = up_node1;
        } else {
            parent[up_node2] = up_node1;
            rank[up_node1]++;
        }
    }

    void unionBySize(int node1, int node2) {
        int up_node1 = findParent(node1);
        int up_node2 = findParent(node2);
        if(up_node1 == up_node2) return;
        if(size[up_node1] < size[up_node2]) {
            parent[up_node1] = up_node2;
            size[up_node2] += size[up_node1];
        } else {
            parent[up_node2] = up_node1;
            size[up_node1] += size[up_node2];
        }
    }
};
```

## BFS, DFS

- shortest path, earliest distance, for uniform weight use BFS with weights added in queue
- for multisources, use bfs by adding all sources in queue initially -> multisource bfs
- normal traversal based - DFS is easier to implement
- do see when do we need to use BFS under `Questions on Djikstras` section

## Topo sort

- dfs: use a stack in normal dfs
- bfs: Kahn's Algo: use an indegree array, push into queue nodes with 0 indegree, then normal bfs
- in a cyclic graph, topo sort in dfs gives a normal dfs traversal and if edges are reversed in bfs, then it gives eventual safe states

## Cycle detection in undirected graph: (BFS)

- well keep doing bfs by storing node and parent in the queue, if you encuonter an adjacent node that is already visited and is not the parent, then there is a cycle.

## Cycle detection in undirected graph: (DFS)

- pass the parent also with node, initially start with {src, -1}. then again for each adjacent node of the traversing node, check if the adjacent node is already visited and is not the parent, then there is a cycle.

## Cycle detection in directed graph: (DFS)

- use 0, 1, and 2 values in the visited array
- 0: not visited
- 1: visited, but part of ongoing traversing path
- 2: visited and not part of ongoing traversing path
- so in normal dfs, check if adjacent node's vis is 0, if yes go on to another dfs call for that node, and in starting of dfs call always mark vis[node] = 1;
- if the adjacent node's vis is 1, it means it was visited and in the same ongoing path, hence a cycle, so return true from there
- if its vis is 2, then it means already visited but not in the ongoing path, so do nothing, just dont write this condition
- if the dfs gets completed for a node and no cycles found, at the end mark vis[node] = 2 and return false.

- you can see the code in one of the gfg problems.

```cpp
bool dfs(int node, vector<int> &vis, vector<vector<int>> &adj) {
   vis[node] = 2;
   for(int it: adj[node]) {
       if(!vis[it]) {
           if(dfs(it, vis, adj)) return true;
       }
       else if(vis[it] == 2) return true;
   }
   vis[node] = 1;
   return false;
```

- check for all unvisited nodes okay

## Cycle detection in directed graph: (BFS)

- easiest
- use Kahn's algorithm for topo sort
- check if topo sort's length is same as that of the number of nodes that is all nodes must be in topo sort, if not, theres a cycle

## Finding eventual safe states:

- in dfs use the 0,1,2 logic, if you find a 1, then thats not a safe state
- use a flag for this, mark flag as false, start and keep marking1 for unvisited, if you encounter a node that is 1 in visiteed, mark flag as true. do not return yet, explore more. if you return you will never traverse for nodes ahead, we need to reach each node to see its state.
- by marking flag as true, we have told that this node is unsafe but we wanna explore more
- so in a node if you dont find any adjacent as 1 and visited, means its a safe state
- for that state in the start, flag must be false, so mark its vis as 2 if flag is false after dfs end
- if that state was unsafe, you wont be able to mark its vis as 2 and you need to return flag to tell your parent that you are safe or unsafe so that it can mark itself accordingly
- nodes with vis 2 are safe states

```cpp
class Solution {
    bool dfs(int node, vector<int> &vis, vector<vector<int>> &graph) {
        vis[node] = 1;
        bool flag = false; //for each node separately
        for(int it: graph[node]) {
            if(!vis[it]) {
                if(dfs(it, vis, graph)) flag = true; //check childs flag was true or false, if true means parent is also unsafe, if false means parent is also safe
            }
            else if(vis[it] == 1) flag = true; //marking flag as true for the first time
        }
        if(!flag) vis[node] = 2; //if all children of parent is safe, parent is safe too so after dfs only do this, this was beautifulll
        return flag;
    }
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> vis(n);
        for(int i = 0; i < n; i++) {
            if(!vis[i]) dfs(i, vis, graph);
        }

        vector<int> safe;
        for(int i = 0; i < n; i++ ) {
            if(vis[i] == 2) safe.push_back(i);
        }

        return safe;
    }
};
```

## Find eventual safe states: (BFS)

- this was again very easy and interesting
- revrse edges (nodes with outdegree as 0 will becomes nodes with indegree as 0 which we need)
- do a topo sort with kahn's
- nodes in topo sort are safe states :))))

## Shortest path in undirected or directed graph with unit weights: (BFS)

- simple bfs algo, bfs ensures that you reach destination from source in min distance
- initialize dist array with -1 and mark dist[src] = 0;
- maintain a distance array. dist[it] where `it` is the adjacent node of src and corresponding nodes in queue = dist[node] + 1, only if dist[it] was -1, otherwise it has been visited and surely has a lower distance from source, coz in bfs as faster as nearer
- where dist[it] = -1, tells cant reach that node from source

## Shortest path in directed acyclic graph with random weights: (Topo)

- TC: $${O(V + E)}$$
- do a topo sort, ensures that before the node we are visiting, all previous ones have been explored
- maintain a distance array like before
- for dfs use a stack for storing topo sort
- dist[src] = 0;
- while(stack is not empty), pop the node out of stack, explore neighbouring nodes
- let `it` be the neighbour, then, dist[it.first] = min(dist[it.first], dist[node_popped_out_of_stack] + it.second)
- youll get the dist array, and points where its inf, make -1

## Shortest path in undirected graph with random weights: (Djikstra)

- TC: $${O(E*log(V))}$$
- helps in finding shortest distance from source to all nodes, if we dont have any negative weight cycle.
- doesnt work on negative weight cycles or negative weights in general
- use a minHeap(standard), set(Fastest_method) or queue(easy but takes time).
- store pair of {weight, node} in minHeap, to init store {0, src} in minHeap
- take the pair out of pq, this has the smallest weight and so we ensure that we are exploring the minimum weight always.
- explore further nodes thru this node
- just check if `dist[it.second] > dist[node_taken_out_of_queue] + it.first`, if yes update dist and push into minHeap, no concept of visited as only pushing nodes in minHeap having least weight for a node.

## Djisktra using other DS:

- each one has {weight, node} to be pushed.
- Queue: expansion of useless paths is too time consuming
- Sets: not much difference in time complexity, but we can erase paths present in set, if we come across another that is shorter

```cpp
set<int> st;
if(dist[it.first] > d + it.second) {
    if(dist[it.first] != inf) {
        st.erase({dist[it.first], it.first});
    }
}
```

- preferred: minHeap

## Questions on Djikstra:

- you'll get a quantity to compute for and put in the minHeap, and min heap decides what will come first
- whenever that qty increases just by 1, use bfs with or without visited array, recommended to use one

### 1st July

## Printing shortest path in undirected graph with unit weights using Djikstra:

- additionally have a parent array initialized as parent[i] = i
- as you come across the condition that `it.second + d < dist[it.first]`, you add {w, n} to the minHeap, update dist[it.first] = d + it.second
- additionally update parent[it] = node;
- then like find operator in union find, trace the path
- you'll have the answer
- trick is having parent array

### 3rd July:

## Bellman Ford algo:

- TC: $$O(V*E)$$

- single source shortest path like djisktra
- applicable for negative weights and detection of negative weight cycles
- djikstra's algo on the other hand runs into infinite loops for negative weights and negative weight cycles
- applicable for directed graphs but can transform undirected to directed graphs by adding edges in both directions with same weight
- the ordering of edges doesnt have anything to do with this algo
- runs for V-1 times
- whenever you see negative weights consider using bellmann ford, that'd be rare

<br>
algo:
- go across all edges, check if the distance of the source node + weight of edge from source to destination is less than the distance of destination vertex, if yes update it. (this is called relaxation as we know in djikstra)
- do this for all edges iterated V - 1 times
- after V-1 iterations, if still there is an updation in the distance matrix, that means there is a cycle coz in max V-1 iterations all the distances must reach to their minimum

```cpp
for(int i = 0; i < V-1; i++) {
    for(auto it: edges) {
        int u = it[0];
        int v = it[1];
        int wt = it[2];
        if( dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
            dist[v] = dist[u] + wt;
        }
    }
}
//detecting negative weight cycle
for(auto it: edges) {
    int u = it[0];
    int v = it[1];
    int wt = it[2];
    if(dist[u] != INT_MAX &&dist[u] + wt < dist[v]) {
        cout << "negative weight cycle";
        return;
    }
}
```

- no formation of adjacency list is required, just use edges array

1. why does it run for v - 1 times only?

- that is because in the worst case you can reach from source to max destination in v - 1 edges, so at max v - 1 iterations will be needed

2. why is it not possible to detect negative weight cycles in bellman ford?

- if the distance array is getting updated even after v - 1 iterations, then there is a negative weight cycle (see the code)

## Floyd Warshall:

TC: $${O(V^3)}$$

- multisource shortest path unlike Bellmann Ford and Djikstra, that is from every vertex we are finding shortest distance to each vertex
- can also detect negative weight cycles and is applicable for negative weights as well
- Doing Djikstra or Bellmann ford for each node instead of just src would be equivalent to this algorithm, however Djikstra wont work for negative weighs and BF gives the same TC as Floyd so no use
- however if its given that there is no negative weight or negative weigth cycle then better go with Djikstra which solves it in ${O(V * E * logV)}$ time.
- works on directed graph but can convert undirected to directed

<br>

algo:

- use an adjacency matrix instead of list, or more specifically use a cost matrix where `cost[i][j] = x` denotes theres an edge between i and j with weight x, if `cost[i][j] = inf or -1` denotes theres no edge
- if the case is of -1 for no edge, first of all convert those -1 to inf and after the algo is complete, convert it back to -1
- `cost[i][i] = 0`, ofc there are no self loops
- the algo states that if we are moving from i to j via another node k (which is always not necessary but those cases are covered), then we can say that updated `cost[i][j] (via k) = minimum of already cost[i][j] and cost[i][k] + cost[k][j]`

- so what are we gonna do is, go across every node that is k ranging from 0 to n - 1 and now in the cost matrix, we'll see if there is an edge between i and k as well as k and j, that is, dist[i][k] != inf and dist[k][j] != inf, if yes, we'll update the cost matrix as `cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j])`
- at last we'll have a matrix, that matrix will be the shortest distance between each node i to j

```cpp
int lim = 1e8;
int n = dist.size();
for(int k = 0; k < n; k++) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(dist[i][k] != lim && dist[k][j] != lim) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
    }
}

//check for negative weight cycles
for(int i = 0; i < n; i++) {
    if(dist[i][i] < 0) {
        cout << "negative weight cycle";
        return;
    }
}
```

- check for negative weight cycles as shown above

## 5th July:

## Minimum Spanning Trees

- valid for weighted graphs (MST not spanning tree, MST is a subset of ST)
- **Spanning Tree**: n nodes, n - 1 edges, connected, all nodes can be reached thru each node, undirected, no cycles. In a completed undirected + weighted graph with n vertices, there are ${(n ^ {n - 2})}$ spanning trees possible. If each edge has a distinct weight then there will be only one unique MST.
- From a graph of n nodes and e edges, there are ${\binom{E}{n - 1} - cycles}$ spanning trees. These cycles are due to edges that form internal cycles.
- example: consider the bidirectional graph: `{[0, 1, 2], [1, 2, 3], [1, 4, 5], [0, 3, 6], [1, 3, 8], [2, 4, 7]}`, then a spanning tree can be: `{[0, 1, 2], [1, 2, 3], [1, 3, 8], [2, 4, 7]}` but this is not the MST.
- **Minimum Spanning Tree**: spanning tree with minimum total weight. Here the MST is: `{[0, 1, 2], [1, 2, 3], [1, 4, 5], [0, 3, 6]}`

## Prim's Algorithm

- TC: $${O(E*logE)}$$
- **Greedy approach**: First select the minimum wt edge and then select minimum wt edge among all edges connected to each node of the tree constructed till yet (selecting min from a node wont ever form a cycle, as you will be selecting only one edge from one node not two at a time that forms a cycle), and so on..
- doest not work for disconnectd graphs

```cpp
int spanningTree(int V, vector<vector<int>> adj[]) {
        // code here
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    pq.push({0, 0, -1}); //pq stores {wt, node, parent}
    vector<int> vis(V);
    vector<vector<int>> mst; //for storing the edges of MST
    int sum = 0; //storing weight of MST
    //dont mark any node as visited beforehand, mark as visited only when you encounter them or pop them from pq

    while(!pq.empty()) {
        vector<int> temp = pq.top();
        pq.pop();
        int wt = temp[0];
        int node = temp[1];
        int par = temp[2];
        if(vis[node]) continue; //if already visited, dont do anything, as its visited with least weight
        vis[node] = 1;
        if(par != -1) { //to check if it wasnt the first node that is 0
            sum += wt;
            mst.push_back({par, node});
        }
        for(auto it: adj[node]) {
            int next = it[0];
            int wnt = it[1]; //weight of next node
            if(!vis[next]) pq.push({wnt, next, node});
        }
    }
    for(auto i: mst) {
        for(int j: i) cout << j << " ";
        cout << " / ";
    } //displaying MST
    return sum; //returning weight
}
```

## Disjoint set union: (DSU)

- TC: $${O(4*alpha) \sim O(1) }$$
- data structure
- use is to find whether a node is in the same component as of another node
- we can do this by conventional bfs or dfs but that would be in O(n), using disjoint set we can do this in constant time
- also its useful when we need to perform the above operation in a dynamic graph, that is a graph that is changing its configuration with time
- dynamic means, in a particular snapshot of graph when its being formed we can use disjoint set to find whether a node is in the same component or not
- DSU consists of two main operations: findParent and unionBySize or unionByRank
- we create components using unionBySize or unionByRank and findParent is used to find whether a node is in the same component or not by checking parents of each node. If `findParent(node1) == findParent(node2)`, then same component.
- algorithm for find and union:

  - **findParent:** finds **ultimate parent** of a node, the ultimate parent is not the immediate parent but the root of the component to which the node is connected to. for example, consider edges [1, 2], [1, 3], [3, 4], [4, 5] then 1 is the ultimate parent of every node. To find the ultimate parent we would do something like, `return findParent(parent[5])` until `parent[node] == node` where `parent` is the vector storing ultimate parent of each node, and initially every node is the parent of itself. This algo for finding parent would take `log(n)` time, that is first find parent of n, then parent of parent of n and so on. But we wanna do it in constant time, so we perform something called `path compression`.
  - In **path compression**, when we find the ultimate parent of 5 for the first time, we also update the parent of 5 to ultimate parent of 5 so that the next time we wanna find ultimate parent of 5, it would be in constant time, that is we would have updated the parent of 5 to ultimate parent of 5 already. We do it by `return parent[5] = findParent(parent[5])`, instead of `return findParent[parent[5]]`.

  ```cpp
  //so:
  int findParent(vector<int> &parent, int node) {
     if(parent[node] == node) return node;
     return findParent(parent, parent[node]); //without path compression
     return parent[node] = findParent(parent, parent[node]); //with path compression
  }
  ```

  - **Union by rank**: Rank is the height of the tree, we use it to make sure that the tree is balanced, so that the time complexity of findParent is constant. We can do this by making sure that the height of the tree is minimum. Technically its not the height but just a factor to tell that one component is superior to another, so make the superior one parent of non superior one. That is ultimate parent of larger rank component becomes the ultimate parent of smaller rank component. Initially rank vector is init as 0. If we union compnonents of same size, then rank of parent becomes +1, otherwise it remains the same. That is larger rank remains the larger only. So the algo is to find the ultimate parent of each node we wanna union, then if the rank of ultimate parent of node1 is smaller than that of node2, `parent[ultimateParentOfNode1] = ultimateParentOfNode2`, otherwise `parent[ultimateParentOfNode2] = ultimateParentOfNode1`, rank remains the same. If both are equal then make any the parent of each other and increase rank of that by 1.

  ```cpp
  void unionByRank(vector<int> &rank, int node1, int node2) {
       int ultimateParentOfNode1 = findParent(parent, node1);
       int ultimateParentOfNode2 = findParent(parent, node2);
       if(rank[ultimateParentOfNode1] < rank[ultimateParentOfNode2]) {
           parent[ultimateParentOfNode1] = ultimateParentOfNode2;
       } else if(rank[ultimateParentOfNode2] < rank[ultimateParentOfNode1]) {
           parent[ultimateParentOfNode2] = ultimateParentOfNode1;
       } else {
           parent[ultimateParentOfNode2] = ultimateParentOfNode1;
           rank[ultimateParentOfNode1]++;
       }
    }
  ```

  - **Union by size**: Rank is not so good factor of comparing the components, so we use size of the components. Doing this we can know the size of the component too where the node is gonna belong or belongs before the union. So instead of comparing rank, we compare size to decide who becomes parent of who. Size is the number of nodes in the component. Init the size array by each node as 1. Then if the size is equal, then make any the parent of each other and increase size of that by size[smallerParentNode]. Otherwise make the smaller parent the parent of the larger one and increase the size of the larger one by the smaller one.

  ```cpp
    void unionBySize(vector<int> &size, int node1, int node2) {
        int ultimateParentOfNode1 = findParent(parent, node1);
        int ultimateParentOfNode2 = findParent(parent, node2);
        if(size[ultimateParentOfNode1] < size[ultimateParentOfNode2]) {
            parent[ultimateParentOfNode1] = ultimateParentOfNode2;
            size[ultimateParentOfNode2] += size[ultimateParentOfNode1];
        } else {
            parent[ultimateParentOfNode2] = ultimateParentOfNode1;
            size[ultimateParentOfNode1] += size[ultimateParentOfNode2];
        }
    }
  ```

- full implementation of DSU class:

```cpp
class DisjointSet {
    vector<int> parent, size, rank;
    public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        size.resize(n + 1, 1);
        parent.resize(n + 1);
        for(int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    int findParent(int node) {
        if(parent[node] == node) {
            return node;
        }
        return parent[node] = findParent(parent[node]);
    }

    void unionByRank(int node1, int node2) {
        int up_node1 = findParent(node1);
        int up_node2 = findParent(node2);
        if(rank[up_node1] < rank[up_node2]) {
            parent[up_node1] = up_node2;
        } else if(rank[up_node1] > rank[up_node2]) {
            parent[up_node2] = up_node1;
        } else {
            parent[up_node2] = up_node1;
            rank[up_node1]++;
        }
    }

    void unionBySize(int node1, int node2) {
        int up_node1 = findParent(node1);
        int up_node2 = findParent(node2);
        if(up_node1 == up_node2) return;
        if(size[up_node1] < size[up_node2]) {
            parent[up_node1] = up_node2;
            size[up_node2] += size[up_node1];
        } else {
            parent[up_node2] = up_node1;
            size[up_node1] += size[up_node2];
        }
    }
};
```

## Kruskal's Algorithm

- **Greedy Approach**: Always select the minimum weight edge that doesn't form a cycle, we need to check for cycles here
- may work for disconnected graph but will give MST for only one connected component
- TC would be ${O(E ^ 2)}$ but with priority queue or min heap, it can be ${O(E log E)}$

```cpp
int kruskalsMST(int V, vector<vector<int>> &edges) {
    // code here
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    DisjointSet obj(V); //use above dsu class
    for(auto it: edges) {
        pq.push({it[2], it[0], it[1]});
        pq.push({it[2], it[1], it[0]});
    }
    int ans = 0;

    while(!pq.empty()) { //n
        vector<int> it = pq.top(); //logn
        int wt = it[0];
        int node1 = it[1];
        int node2 = it[2];
        pq.pop();
        if(obj.findParent(node1) != obj.findParent(node2)) { //constant
            ans += wt;
            obj.unionByRank(node1, node2); // constant
        }
    }
    //nlogn

    //if wud have used a vector instead of pq, then o(1) for accessing and nlogn for sorting

    return ans;
}
```

## Applications of DSU:

- **Counting components in a graph**:

```cpp
int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    DisjointSet obj(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(isConnected[i][j]) {
                obj.unionByRank(i, j); //do union of every existing edge, union(1, 1) = nothing
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < n; i++) {
        if(obj.findParent(i) == i) ans++; //boss is the one who is parent of itself, no. of bosses = no. of components
    }
    return ans;
}
```

- **For online queries**: number of islands (gfg)
- **For watching when or at what point two nodes become connected**: swim in rising water(leetcode)

## 9th July

## Strongly Connected Components (SCC):

- a component in which every node all edges are like, if there is an edge from node1 to node2, the node2 must be reachable from node1 as well.
- only applicabe in directed graphs
- consider a graph with edges 0 2, 2 1, 1 0, 0 3, 3 4, 4 3, 3 6
- here 0 2 1 is one SCC as 0 -> 2 -> 0 is possible, 2 -> 1 -> 2 is possible and so on, similarly 3 4 is another SCC and 6 individually is an SCC
- so we mostly need to tell the number of SCC or print all SCC
- therefore if we move from forward and backward, if we are accessing the same nodes then those nodes belong to an SCC
- there is a thought process that, if we reverse all the edges (moving backwards), and explore from nodes in order of finishing time(that is in order they were visited in the unreversed graph), then all the nodes that are connected to each other will be in the same SCC
- therefore we can say that, if we are able to find the SCC of the reversed graph, then that SCC is the SCC of the original graph. Those which became disconnected were clearly note part of an SCC
- for example consider in a graph 3 -> 4 is there but not 4 -> 3. Then forward traversal would have 4 then 3, as 4 finished first. then we reverse edges. we start from the one which finished the last (As that would be the node from where we started in dfs). Later when we move from 3 we cant access 4 in the reversed graph, therefore 3 -> 4 is not an SCC, however if there was an edge from 4 -> 3 in the graph too, then we would have been able to access and in forward or backward traversal we would have 4 -> 3, 3 -> 4 counted as one component only

- hence we follow something called **Kosaraju's Algorithm** to find the SCC of a graph

## Kosaraju's Algorithm

- TC: $${O(V + E)}$$

- store the nodes in order of their finish time, the one with last finish time is at the top.
- for this use dfs in actual graph + stack (same as topo sort using dfs)
- reverse edges
- take node one by one from top of stack and start performing dfs in reversed graph. (the nodes taken will be in same order as they were in the original graph)
- if a node is already visited, it means its part of same SCC
- if not visited then its a new SCC, start dfs from there after counting + 1 for new SCC
- implementation:

```cpp
class Solution {
    void dfs(int node, vector<int> &vis, vector<vector<int>> &adj, stack<int> &st) {
        vis[node] = 1;
        for(int it: adj[node]) {
            if(!vis[it]) dfs(it, vis, adj, st);
        }
        st.push(node);
        return;
    }
    void dfs1(int node, vector<int> &vis, vector<vector<int>> &radj) {
        vis[node] = 1;
        for(int it: radj[node]) {
            if(!vis[it]) dfs1(it, vis, radj);
        }

        return;
    }
public:
    int kosaraju(vector<vector<int>> &adj) {
        // code here
        int n = adj.size();
        stack<int> st;
        vector<int> vis(n);
        for(int i = 0; i < n; i++) {
            if(!vis[i]) dfs(i, vis, adj, st);
        }
        stack<int> st1;
        vector<vector<int>> radj(n);
        for(int i = 0; i < n; i++) {
            for(auto it: adj[i]) {
                radj[it].push_back(i);
            }
        }
        for(int i = 0; i < n; i++) vis[i] = 0;
        int ans = 0;
        while(!st.empty()) {
            int node = st.top();
            st.pop();
            //for printing initialize an empty vector and pass to dfs for inserting
            //init a vectors of vector outside loop and insert that vector in it
            if(!vis[node]) {
                ans++;
                dfs(node, vis, radj, st1);
            }

        }
        return ans;

    }
};
```

## Bridges in Graph

- A bridge in a graph is an edge that, if removed, causes the graph to split into 2 or more components, or makes it disconnected.
- for this we use Tarjan's Algorithm

## Tarjan's Algorithm

TC: $$O(V + 2E)$$

- tc is for undirected graph, for directed ${O(V + E)}$

- so what we do in this algo is that we use dfs and we keep track of the time of the node and the low value of the node. Low value is the least steps it would take for a node to be reached from the source. if its less than its parent, it means there is another way of reaching out to the node except just the parent and hence the edge between the node and the parent will not be a bridge.
- however if its greater than that of the parent, then it means that the node cant be reached in any other way except the parent and therefore the edge between the node and the parent will be a bridge.
- its better if you watch strivers video again for this but above was the jist for it.
- ill give you the algo
  <br>

**Algorithm:**

- traverse to the nodes that are adjacent in dfs fashion
- if you reach the end and there are no more nodes to be traversed, you look at your adjacents' low values
- the low value of the node is the minimum of its adjacent nodes'
- after updation you check whether the node's low value is greater than its parent's low value, if yes then you have a bridge and add {par, node} as a bridge in bridges

- **starred:** make sure after you complete child's dfs and come back to the parent's recursion call, then only you update the low value, but not the actual low value otherwise for the other child it will be a nightmare. Take a case where one of your child updated its low value to something way lower than the parent's coz the child was connected from another route, now you updated it as soon as dfs of child ended. Now when you traverse another child, the child will compare its updated low value from that of parents, and parents was already updated to very low due to that other child. So you will get a wrong answer.
- hence to avoid this you store the low value in mini variable, and keep calculating mini = min(mini, low[child_node_just_completed_dfs]) for visited and unvisited nodes' dfs completion.
- after the completion of dfs for all of its chlidren, then only you update the parent's low value and check with grandparent's one for a bridge
- for doing this striver used a `tin` vector for saving parent's low value getting updated, but this one i wrote is better and more intuitive

- so here's the implementation:

```cpp
class Solution {
    void dfs(int node, int par, int timer, vector<int> &vis, vector<int> &low, vector<vector<int>> &adj, vector<vector<int>> &bridges) {
        int mini = timer;
        low[node] = timer;
        vis[node] = 1;
        for(int it: adj[node]) {
            if(it == par) continue;
            if(!vis[it]) {
                dfs(it, node, timer + 1, vis, low, adj, bridges);
                mini = min(mini, low[it]); //here i was talking about updation, if you dont then update you'll miss this value and would never be able to update it, also cant directly do low[node] = min(mini, low[it]) coz then that problem will arise that i starred without using tin. so you update mini and altogether update low value at last
            } else {
                mini = min(mini, low[it]);
            }
        }
        low[node] = min(mini, timer);
        if(low[node] > low[par]) bridges.push_back({node, par});
        return;
    }
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> adj(n);
        for(auto it: connections) {
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }

        vector<int> vis(n), low(n, INT_MAX);
        vector<vector<int>> bridges;
        dfs(0, 0, 0, vis, low, adj, bridges);
        return bridges;
    }
};
```

- you can also get rid of vis, by using low only as vis, if low is INT_MAX, measn that node was never visited coz for every visited node we are doing low[node] = timer before starting dfs

### here's an intersting observation: you can find number of bridges by Kosaraju's algorithm and strongly connected components by Tarjan's algorithm.

## Articulation Point

- a node in a graph, if removed, splits the graph into two or more components, then that node is called an articulation point.
- a node is an articulation point if it has two or more children, or if it has a child and that child has two or more children. (technically)
- to find articulation points we use a modification of Tarjan's algorithm.
- so in the above code, there was an observation that what we used as low[it] in the visited condition was more or less the timer of `it` and not the low value of it. Its because we are updating the low value only after completing its dfs. And if we are on a node and we are able to access the visited, it means the visited node has not yet completed its dfs, therefore for that node, `low[that_node] = timer` still.
- it still worked because if the low value is same for node and parent, then too a bridge wasnt there.
- `however in the articulation point, we need to check with the timer only and not the actual low value of the parent node. so our above code works in this without modification in the condition for visited that: `mini = min(mini, low[it])`.` If we would have used the low of the parent node, the low value might have got very low due to completion of dfs of the other child. Now when another node comes back to this parent node from another parent, then it updates its low value of this node, and it completes its dfs too. then it checks if theres an articulation point but it would have gone false due to false updation of low. Hence use timer
  (for better view please watch striver when hes going thru the algo at node 7)
  <br>

**More important poitns:**

- so the only modified condition is: `low[node] >= low[parent]` then articulation point. in bridge it was only greater and not equal. here even if its equal then too coz the parent is gonna get removed only so all edges that come from parent to node will be removed. in bridge if one edge from parent to node was removed, another edge from parent to node thru other nodes might have saved the graph from being disconnected. so in bridge it was only greater and not equal.
- also this condition is only valid for nodes whos direct parent is not the source node(0 in most of the cases). thats because then we'll have to check the number of children of that node and all other nodes with direct parent as 0. So just ignore the node if its parent is 0
- for 0 or source node, you count the nodes that are unvisited from it, and only those nodes will get separated if 0 is removed. if those children are > 1 then def 0 is an AP
- use a mark array to mark the AP, and if the first condition is true, parent will be an AP not the child, coz ofc you can draw and check.

- code:

```cpp
class Solution {
    void dfs(int node, int par, int timer, vector<int> &vis, vector<int> &low, vector<int> &mark, vector<int> adj[]) {
        vis[node] = 1;
        low[node] = timer;
        int mini = timer;
        int count = 0;
        for(int it: adj[node]) {
            if(!vis[it]) {
                count++;
                dfs(it, node, timer + 1, vis, low, mark, adj);
            }
            mini = min(mini, low[it]);
        }
        low[node] = min(mini, low[node]);
        if(par && low[node] >= low[par] && !mark[par]) mark[par] = 1;
        if(!node && count > 1) mark[par] = 1;
    }
  public:
    vector<int> articulationPoints(int V, vector<int> adj[]) {
        // Code here
        vector<int> vis(V), mark(V), low(V);
        dfs(0, 0, 0, vis, low, mark, adj);
        vector<int> nodes;
        int ans = 0;
        for(int i = 0; i < V; i++) {
            if(mark[i]) nodes.push_back(i);
        }

        // sort(nodes.begin(), nodes.end());
        if(nodes.empty()) return {-1};
        return nodes;

    }
};
```
