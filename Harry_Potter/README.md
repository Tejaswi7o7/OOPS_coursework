# Harry Potter and Enchanted Even Paths

## Problem Statement
The Gryffindor common room clock chimes past lights out, but Harry isn’t in bed. He’s on a mission. Fred and George Weasley’s greatest prank yet —a dazzling display of Weasleys’ Wildfire Whiz-bangs—depends on him retrieving their last batch of fireworks before Filch finds them. To do this successfully, the Weasley twins have given the Marauder’s Map to Harry.  

The Marauder’s Map reveals Hogwarts as a simple, undirected graph: rooms as nodes, secret passages as edges, where each passage has a travel time associated with it. Harry wants to know the shortest path to the fireworks, but that’s not all. Ever since his last encounter with Voldemort, Harry has a rather odd fear of paths with an odd number of passages. Therefore, he must use the shortest path to the fireworks while ensuring it contains an even number of passages.  

To navigate efficiently, Harry recalls Hermione’s lessons on data structures and algorithms. Since Hermione taught him about minimum priority queue, he is comfortable only with those. However, STL priority queue was implemented by Professor Snape, and he always has information about which student uses his spells (and implementations). And Harry definitely doesn’t want the professor to learn about his mischief. Therefore, he needs to implement a generic minimum priority queue first, to find the shortest path.

## Methods
Implement the following functions. You can use any additional functions as per your requirements.
- `const size_t size() const`: Returns the number of elements currently stored in the priority queue.
- `void push(const T&)`: Inserts a new element into the priority queue while preserving its heap property in O(log n) time.
- `void pop()`: Removes the top (minimum) element from the priority queue in O(log n) time.
- `const T& top() const`: Retrieves the top (minimum) element from the priority queue without removing it.
- `const bool empty() const`: Checks whether the priority queue is empty, returning true if it contains no elements.

## Constraints
- ( 2 <= n <= 1x10^(5) , 1 <=m <= 1x10^(5) )  
- Length of a room ID is atmost 100 characters  
- Edge weights are positive. Total path weight between any two vertices will not exceed 2x10^(9)  
## Input Format
1. The first line of each test case contains n and m, which represent the number of rooms and number of bidirectional passages respectively. 
2. Following n lines contain n unique room IDs. Each room ID is an alphanumeric string and corresponds to a unique room.
3. Following m lines contain one edge each in the form ai, bi, wi, where ai and bi represent the room IDs and wi represents the time it takes to traverse this edge.
4. The last line contains two room IDs: room ID of the source and room ID of the destination.

## Output Format 
Print a single integer, representing the minimum time required to traverse an even-length path from the source to the sink.

If such a path does not exist, print -1.

