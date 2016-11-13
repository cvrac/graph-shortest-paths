SIGMOD PROGRAMMING CONTEST 2016

Implemented by Yannis Papatsoris, Christos Vrachas

In graph theory, the shortest path problem is the problem of finding a path between two vertices (or nodes) in a graph such that the sum of the weights of its constituent edges is minimized. This is a fundamental and well-studied combinatorial optimization problem with many practical uses: from GPS navigation to routing schemes in computer networks; search engines apply solutions to this problem on website interconnectivity graphs and social networks apply them on graphs of peoples' relationships.

In this contest, the task is to answer shortest path queries on a changing graph, as quickly as possible. We will provide an initial graph which you may process and index in any way you deem necessary. Once this is done, we will begin issuing a workload consisting of a series of sequential operation batches. Each operation is either a graph modification (insertion or removal) or a query about the shortest path between two nodes in the graph. Your program is expected to correctly answer all queries as if all operations had been executed in the order they were given.

The graphs are directed and unweighted. Input to your program will be provided via standard input, and the output must appear on the standard output.

http://dsg.uwaterloo.ca/sigmod16contest/task.html

# Development Notes
- Google testing setup: κατεβαζεις το ρεπο, extract, εκτελεις make μεσα στο googletest-master/googletest/make, μετονομαζεις το gtest_main.a σε libgtest_main.a , 
φροντιζεις οι μεταβλτητες GTEST_INCLUDE και GTEST_LIBDIR του graph-shortest-paths/tests/Makefile να δειχνουν στο σωστο σημειο, εκτελεις make.

# Part 2 notes
1. Εύρεση Connected Components
- Απλός αλγόριθμος, bfs/dfs για κάθε κόμβο στο Index. Non-recursive
- Σε κάθε αναζήτηση, όλοι οι κόμβοι που γίναν visit, σημαίνει ότι υπάρχουν
στην ίδια συνεκτική συνιστώσα.

2. Εύρεση Strongly Connected Components
- Η διαφορά τους έγγυται στο γεγονός ότι μια τέτοια συνιστώσα είναι ένα
υποσύνολο κόμβων, για το οποίο για κάθε δύο κόμβους που ανήκουν σ' αυτό,
υπάρχει μονοπάτι που τους συνδέει
- Χρήση του αλγορίθμου Tarjan, που βασίζεται στον dfs. Non-recursive και
χρήση δομών που θα βοηθήσουν στην ταχύτερη εκτέλεσή του.


Υπάρχει ένα μπέρδεμα στου αν θα πρέπει να κρατούνται χωριστά τα connected
components από τα strongly connected components, ή ακόμη και το αν θα 
πρέπει να κρατούνται τα πρώτα. Στην εκφώνηση, δεν
αναφέρεται κάτι συγκεκριμένο επ' αυτού, πέραν της δομής SCC, και της
Component. Η Component, κρατά πληροφορία για ένα συγκεκριμένο component,
ενώ η SCC, συνολικά για όλα. Επίσης, στο SCC, φαίνεται πως υπάρχει
κι ένας πίνακας invrted index φάση, ο οποίος απ' ότι έχω καταλάβει θα 
βοηθήσει σε γρηγορότερο lookup του σε ποιο component ανήκει κάποιος κόμβος.

3. Grail index για ανίχνευση μεταβατιότητας.
- Περιγραφή του Grail, στο παρακάτω paper: 2 http://www.vldb.org/pvldb/vldb2010/papers/R24.pdf
- Βοηθάει στο να επιταχυνθούν τα shortest path queries. Συγκεκριμένα, 
εξασφαλίζει αρκετά ταχύτερη απάντηση στην περίπτωση που δεν υπάρχει μονοπάτι,
με βεβαιότητα. Αντίθετα, σε περίπτωση που μπορεί να υπάρχει μονοπάτι,
θα πρέπει να πραγματοποιηθεί κανονικά το query.

4. Grail Index Creation
- Διαφορετική διαχείρηση στην περίπτωση που υπάρχουν κύκλοι για τη δημιουργία, όπου βρίσκουμε τα strongly connected components, δημιουργώντας έτσι έναν υπεργράφο, όπου κάθε scc συνιστά έναν νέο κόμβο, και οι ακμές που μένουν είναι αυτές που συνδέουν κάθε κόμβο με έναν άλλο στον υπεργράφο. Λίγο μπέρδεμα κι εδώ στο αν θα πρέπει να διακρίνουμε 2 περιπτώσεις, ή απλά να θεωρήσουμε οτι πάντα υπάρχουν κύκλοι, άρα αυτό το στεπ θα πρέπει να γίνεται πάντα.
- Queries μεταβατικότητας:
X -> Y ?.
a) Έλεγχος του αν τα X, Y ανήκουν στο ίδιο component. Αν ναι, τότε τέλος,
αλλίως, χρησιμοποιούμε το GRAIL κι ελέγχουμε τη συνθήκη
Αν Y{[min_rank, rank]} <= X{[min_rank, rank]}
τοτε no
αλλιώς ίσως.

Αν έχουμε no, τότε επιστροφή -1, αν είναι yes, τότε εκτελούμε
shortest path query εντός ενός scc, αλλιώς αν είναι maybe, αναζήτηση
σε ολόκληρο το γράφο.

5. Ενσωμάτωση grail και διαφορετική διαχείρηση Dynamic/Static Graphs στο
πρόβλημα

