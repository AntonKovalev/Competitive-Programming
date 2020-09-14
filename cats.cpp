// Example program
#include <algorithm>
#include <vector>
#include <iostream>
#include <tuple>
#include <limits>
#include <deque>
#include <queue>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <sstream> // std::stringstream
#include <stack>   // std::stack
#include <utility> // std::pair
using namespace std;

int64_t find(vector<int64_t> &parent, int64_t a)
{
    // If i is the parent of itself
    if (parent[a] == a)
    {
        // Then i is the representative
        return a;
    }
    // Recursively find the representative and move
    // each node up the tree, so that all nodes point directly to
    // the parent.
    return parent[a] = find(parent, parent[a]);
}

bool join(vector<int64_t> &parent,
          vector<int64_t> &rank,
          int64_t a,
          int64_t b)
{
    a = find(parent, a);
    b = find(parent, b);
    if (a == b)
        return false;

    // If i’s rank is less than j’s rank
    if (rank[a] < rank[b])
    {
        // Then move i under j
        parent[a] = b;
    }

    // Else if j’s rank is less than i’s rank
    else if (rank[a] > rank[b])
    {
        // Then move a under b
        parent[b] = a;
    }

    // If ranks are same, then increment rank.
    else
    {
        parent[b] = a;
        rank[a]++;
    }
    return true;
}

bool isSameSet(vector<int64_t> &parent, int64_t i, int64_t j)
{
    return find(parent, i) == find(parent, j);
}

void makeSet(vector<int64_t> &parent,
             vector<int64_t> &rank,
             int64_t N)
{
    //parent.assign(N, 0);
    for (int i = 0; i < N; ++i)
        parent[i] = i;
    rank.assign(N, 0);
}

using ii = pair<int64_t, int64_t>;

int64_t kruskal(vector<pair<int64_t, ii>> &EdgeList, int64_t E, int64_t V)
{
    // (weight, two vertices) of the edge
    /*for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        // read the triple: (u, v, w)
        EdgeList.push_back(make_pair(w, ii(u, v)));
    }*/
    // (w, u, v)
    sort(EdgeList.begin(), EdgeList.end()); // sort by edge weight O(E log E)
    // note: pair object has built-in comparison function
    int64_t mst_cost = 0;
    vector<int64_t> parent;
    parent.resize(V);
    vector<int64_t> rank;
    makeSet(parent, rank, V);
    // all V are disjoint sets initially
    for (int i = 0; i < E; i++)
    {
        // for each edge, O(E)
        pair<int64_t, ii> front = EdgeList[i];
        if (!isSameSet(parent, front.second.first, front.second.second))
        { // check
            mst_cost += front.first;
            // add the weight of e to MST
            join(parent, rank, front.second.first, front.second.second);
            // link them
        }
    }
    // note: the runtime cost of UFDS is very light
    // note: the number of disjoint sets must eventually be 1 for a valid MST
    //printf("MST cost = %d (Kruskal’s)\n", mst_cost);
    return mst_cost;
}

int main()
{
    int64_t t, m, c, d;
    cin >> t;
    while (t != 0)
    {
        vector<pair<int64_t, ii>> edgeList;
        cin >> m >> c;

        int edges = c*(c-1)/2;

        if(c == 1)
        {
            cout << "yes" <<endl;
            t--;
            continue;
        }

        int64_t i, j;
        for (int a = 0; a < edges; ++a)
        {
            cin >> i >> j >> d;
            edgeList.push_back(make_pair(d, ii(i, j)));
        }

        int64_t mst_cost = kruskal(edgeList, c*(c-1)/2, c);
        
        if(mst_cost + c <= m)
        {
            cout << "yes" <<endl;
        }
        else
        {
            cout << "no" <<endl;
        }
        

        t--;
    }
    return 0;
}
