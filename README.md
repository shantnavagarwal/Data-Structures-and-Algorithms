# Data-Structures-and-Algorithms
This Repository implements various Data Structures and Algorithms in C++. There are 3 programs.

## A2
### Implements a Sparse matrix using Cicular Multi-Linked List. Supports following Operations:
1. AddLink <from-page-i> <to-page-j>: Increments M[j][i] by 1. If node for M[j][i] does not already exist, creates a new node for M[j][i] in the multilist and initialize it with 1. <br>
2. DeleteLink <from-page-i> <to-page-j>: Reduces the value M[j][i] by 1. If after the operation the value reduces to 0 then removes the node corresponding to M[j][i] in the multi list. Ignores if M[j][i] is 0 (i.e. no node in the multi list for it). <br>
3. RetrieveValue <from-page-i> <to-page-j>: Returns the number of links from page i to j i.e. M[j][i].<br>
4. RetrieveRowSumUptoKthColumn <page-i> <k>: Returns sum of values ﬁrst k columns in the row i in matrix M up (i.e. M[i][0...k-1]).<br>
5. RetrieveColumnSumUptoKthRow <page-i> <k>: Returns sum of values ﬁrst k rows in the column i in matrix M up (i.e. M[0...k-1][i]). <br>
6. MultiplyVector <n> <n-space-separated-value>: Multiplies the (n x n) sub matrix of M having upper leftmost element as M[0][0] (i.e. M[0...n-1][0...n-1]) with the given vector (n x 1). <br>
7. FindPageWithKthHighestOutwardLinks <k>: Returns the page number with k-th highest count of outward links. If there are multiple such pages, returns the one with the smallest page number

## A3
### Implements a Market Data Publisher using a balanced AVL Tree. Supports following  operations:
1. register-company <company-id> <initial-price>: Inserts a new node in the AVL Tree with the given company-id and price. Prints the company-id and the stock price separated by a space(see output format).<br>
2. deregister-company <company-id>: Removes all data of the company with the given company-id. <br>
3. update-price <company-id> <new-price>: Updates the price of the given companyid, if the above given rule is satisﬁed. Also in case the rule is satisﬁed, it broadcasts (print) the current price. Ignores operation if given stock does not exist. 
4. stock-split <company-id> <x:y>: Updates the price of the company-id given that its stocks are split in the ratio x−for−y. (Note: This operation also covers reverse stock split, i.e. it is possible that x < y.) Publishes (print) the updated stock price. Ignores operation if given stock does not exist.

## A4
### Implements a Minimum Spanning Tree to connect prime junctions of a newly estabilished township. It further implements Djikstra's Algorithm to minimize travel time taking into consideration traverse time and traffic light time. Supports following functions:
  1. Add-junction (x)(y): Adds a junction x with traffic light time = y.<br>
  2. add-road: Adds a road between junction i and j with build time = m and traverse time = n. <br> 
  3. demolish-road (i) (j): Demolishes the road between the prime point i and j. <br>
  4. print-mst: Prints the roads (represented as (x y) where x < y and the road connects junctions x and y) in the minimum spanning tree of the current junction-road graph ordered such that if a road (x1 y1) is placed before (x2 y2), then either x1 < x2 or if x1 = x2 then y1 < y2. If multipleMSTs exist, then output any one of them. If there is tree spanning all vertices, just output -1.<br>
  5. quick-travel (i) (j): Prints the minimum time needed to reach junction j starting at i at time 0. Also, outputs the junction ids in order of your suggested visit.
## Please refer to .pdf for the complete problem statement
