For implementation, I used an adjacency list and a road matrix, because in the adjacency list the Graph
remained unchanged, and for task2 I needed to modify the matrix.
Thus, always building the matrix based on the adjacency list, I managed to keep it 'intact'.

Task1: (display the cost from node a to node b and the way)

To solve the task, we implemented an algorithm, costMinimFromNodeToNode, which recursively calls neighboring nodes
always changing start. I kept the minimum of the solution in the answer. (If answer > as edge + the previous way) I update
the answer, the same principle as at dijkstra (the answer is d[start], where d is the vector of distances, but the algorithm
itself is a DFS).
To display the road, I retained a vector of fathers that I called recursively from the end to the beginning in order to
save in the ground vector the road. The solution was represented by displaying the solution vector from the end to the beginning
(twice, because we had the road from a to b and from b to a).

Task 2: (number of strongly connected components in O(n*n))

To solve task 2, I used a simple DFS. As long as an optimization of the algorithm was not requested
I used a not very efficient solution, but easy to write.
I used DFS to find out if there is a route from node i to node j. Thus for each node j i used
the algorithm to see if there is a path to all the rest of the nodes. If there is a road from i to j and a road
from j to i => that they are part of the same strongly connected component. I used this algorithm once to see
how many hard connected components I have (count how many DFSs I have) and once again to display all the nodes i are part of
from the same component connected with j.

Task 3: (Minimum cost from a to b, but going through all nodes, how many times we want to)

In solving task 3, we approached a modified version for Dijksta. Normally Dijkstra retains the minimum cost
from a start node to the other nodes. By adding the bit mask, the implementation changes the value of the cost and in
the case where the cost was higher but I had visited more nodes. For example, starting from node 0, I can reach the node
3 through the path 0-1-2-3 of cost 15 or through the path 0-3 of cost 4. The bit mask for the first path contains several
values ​​of 1 (1111) while for the second it contains 1001. Thus the algorithm will save the cost 15 in the distance vector
and mask 1111. If another 0-2-1-3 route with cost 14 is found, it has mask 1111 and will be saved in the vector
distance for 3 value 14 and mask 1111.
The rest of the implementation is a Dijkstra, starting from a node, adding the neighboring nodes to the queue, marking
as visited when we go through them and if a node is unvisited I add its neighbors to the queue. It is running
the algorithm as long as the queue is not empty.
