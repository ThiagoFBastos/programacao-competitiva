# Tutorial of how i solved the following problems

- [A + B](https://github.com/ThiagoFBastos/competitive-programming/blob/main/yosupo/A%20%2B%20B.rs) 
    
    Simple algorithm to sum up two integers.

- [Associative Array](https://github.com/ThiagoFBastos/competitive-programming/blob/main/yosupo/Associative%20Array.rs)

    Used a BTreeMap to simulate an array of infinite length.

- [Connected Components of Complement Graph](https://github.com/ThiagoFBastos/competitive-programming/blob/main/yosupo/Connected%20Components%20of%20Complement%20Graph.rs)

    Here we store the vertices that have not been visited yet in a BTreeSet and perform a BFS, picking vertices from the sorted adjacency list and focusing on those that lie between two vertices in the list (with special cases for the first and last elements).

- [Deque](https://github.com/ThiagoFBastos/competitive-programming/blob/main/yosupo/Deque.rs)

    Simple deque operations using Rust VecDeque.

- [Double-Ended Priority Queue](https://github.com/ThiagoFBastos/competitive-programming/blob/main/yosupo/Double-Ended%20Priority%20Queue.rs)

    Here we simulated a std::multiset of C++ to get the min and max elements of a set. To do this we used a BTreeMap where the key is the element and the value is the count of these keys.

- [Enumerate Palindromes](https://github.com/ThiagoFBastos/competitive-programming/blob/main/yosupo/Enumerate%20Palindromes.rs)

    Straightforward application of Manacher algorithm.

- [Jump on Tree](https://github.com/ThiagoFBastos/competitive-programming/blob/main/yosupo/Jump%20on%20Tree.rs)

    Here we used a lowest common ancestor algorithm based on binary lifting and we found the k-th vertex making jumpings using the sparse table

- [Longest Increasing Subsequence](https://github.com/ThiagoFBastos/competitive-programming/blob/main/yosupo/Longest%20Increasing%20Subsequence.rs)

    Simple algorithm that uses binary search to find the LIS that a specific number belongs

- [Lowest Common Ancestor](https://github.com/ThiagoFBastos/competitive-programming/blob/main/yosupo/Lowest%20Common%20Ancestor.rs)

    Simple straightforward application of LCA + binary lifting algorithm

- [Many A + B (128 bit)](https://github.com/ThiagoFBastos/competitive-programming/blob/main/yosupo/Many%20A%20%2B%20B%20(128%20bit).rs)

    Simple algorithm to sum up two 128 bit integers.

- [Many A + B](https://github.com/ThiagoFBastos/competitive-programming/blob/main/yosupo/Many%20A%20%2B%20B.rs)
    Simple algorithm to sum up two integers.

- [Maximum Independent Set](https://github.com/ThiagoFBastos/competitive-programming/blob/main/yosupo/Maximum%20Independent%20Set.rs)

    Here we used the meet-in-the-middle technique to find the maximum independent set.
    In the first part, we found the largest subset of vertices whose induced graph is an independent set and that is a subset of a given set.
    In the second part, given an induced graph that is an independent set, we find the largest independent set from the first part that is a subset of the complement of its neighborhood.

- [Minimum Spanning Tree](https://github.com/ThiagoFBastos/competitive-programming/blob/main/yosupo/Minimum%20Spanning%20Tree.rs)

    Simple Kruskal MST algorithm