SIGMOD PROGRAMMING CONTEST 2016

Implemented by Yannis Papatsoris, Christos Vrachas

In graph theory, the shortest path problem is the problem of finding a path between two vertices (or nodes) in a graph such that the sum of the weights of its constituent edges is minimized. This is a fundamental and well-studied combinatorial optimization problem with many practical uses: from GPS navigation to routing schemes in computer networks; search engines apply solutions to this problem on website interconnectivity graphs and social networks apply them on graphs of peoples' relationships.

In this contest, the task is to answer shortest path queries on a changing graph, as quickly as possible. We will provide an initial graph which you may process and index in any way you deem necessary. Once this is done, we will begin issuing a workload consisting of a series of sequential operation batches. Each operation is either a graph modification (insertion or removal) or a query about the shortest path between two nodes in the graph. Your program is expected to correctly answer all queries as if all operations had been executed in the order they were given.

The graphs are directed and unweighted. Input to your program will be provided via standard input, and the output must appear on the standard output.

http://dsg.uwaterloo.ca/sigmod16contest/task.html

# Development Notes
- Google testing setup: κατεβαζεις το ρεπο, extract, εκτελεις make μεσα στο googletest-master/googletest/make, μετονομαζεις το gtest_main.a σε libgtest_main.a , 
φροντιζεις οι μεταβλτητες GTEST_INCLUDE και GTEST_LIBDIR του graph-shortest-paths/tests/Makefile να δειχνουν στο σωστο σημειο, εκτελεις make.

- Θα πρεπει να βρουμε μια καλη τιμη για τον αριθμο των γειτονων N ανα listNode.
 Ο μεγαλυτερος δυνατος γραφος μπορει να αποτελειται απο A = 2,814749432 * 10^14 ακμες, 
 αρα θα πρεπει να φροντισουμε το πεδιο ListNodePos::pos να ειναι τετοιου τυπου ωστε
  να μπορει να αναπαραστησει τον αριθμο Α / Ν.