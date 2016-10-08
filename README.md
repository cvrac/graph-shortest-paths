In graph theory, the shortest path problem is the problem of finding a path between two vertices (or nodes) in a graph such that the sum of the weights of its constituent edges is minimized. This is a fundamental and well-studied combinatorial optimization problem with many practical uses: from GPS navigation to routing schemes in computer networks; search engines apply solutions to this problem on website interconnectivity graphs and social networks apply them on graphs of peoples' relationships.

In this contest, the task is to answer shortest path queries on a changing graph, as quickly as possible. We will provide an initial graph which you may process and index in any way you deem necessary. Once this is done, we will begin issuing a workload consisting of a series of sequential operation batches. Each operation is either a graph modification (insertion or removal) or a query about the shortest path between two nodes in the graph. Your program is expected to correctly answer all queries as if all operations had been executed in the order they were given.

The graphs are directed and unweighted. Input to your program will be provided via standard input, and the output must appear on the standard output.

http://dsg.uwaterloo.ca/sigmod16contest/task.html
