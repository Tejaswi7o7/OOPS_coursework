# Graph Operations with Operator Overloading

## Problem Statement
Implement a `Graph` class that represents an undirected graph and supports various operations using operator overloading. 

**Methods**:  
- `operator+`: Union of two graphs
- `operator-`: Intersection of two graphs
- `operator!`: Complement of a graph
- `operator>>`: Input a graph
- `operator<<`: Output a graph
- `isReachable`: Check if there's a path between two vertices
- `addEdge`: Add an edge between two vertices
- `removeEdge`: Remove an edge between two vertices  

**Formal Definitions**:
1. Union of Graphs (G1 + G2)  
Let G1(V1, E1) and G2(V2, E2) be two graphs. The union of G1 and G2 is a graph G = G1 ∪ G2, where:
- Vertex set V = V1 ∪ V2
- Edge set E = E1 ∪ E2  
2. Intersection of Graphs (G1 - G2)
Let G1(V1, E1) and G2(V2, E2) be two graphs. The intersection of G1 and G2 is a graph G = G1 ∩ G2, where:
- Vertex set V = V1 ∪ V2
- Edge set E = E1 ∩ E2  
3. Complement of a Graph (!G)
Let G(V, E) be a simple graph and K be the set of all 2-element subsets of V. The complement of G, denoted as G', is defined as: G' = (V, K \ E) Where K \ E is the relative complement of E in K. In other words, the complement graph has:
- The same vertex set V as the original graph
- An edge between two vertices if and only if there is no edge between them in the original graph

**Operations**:
- `union`: Followed by another graph definition (using the overloaded >> operator)
- `intersection`: Followed by another graph definition (using the overloaded >> operator)
- `isReachable` `u` `v`: Check if vertex v is reachable from vertex u
- `add_edge` `u` `v`: Add an edge between vertices u and v. If the edge already exists, do nothing.
- `remove_edge` `u` `v`: Remove the edge between vertices u and v. If the edge doesn’t exist do nothing.
- `printGraph`: Display the current state of the graph (using the overloaded << operator)
- `end`: Terminate the program

## Input Format
The input consists of multiple operations:
- First line: `Graph`
- Second line: `N` `M` (N = number of vertices, M = number of edges)
  - 1 ≤ N ≤ 10^3 
  - 0 ≤ M ≤ min(N * (N-1) / 2, 10^5)
- Next M lines: `u` `v` (representing an edge between vertices u and v)
- Subsequent lines: Various operations as described below

## Output Fromat
- For `isReachable`: Print "Yes" if reachable, "No" otherwise
- For `printGraph`: Use the overloaded << operator to display each vertex and its adjacent vertices
- For other operations: No output unless specified
