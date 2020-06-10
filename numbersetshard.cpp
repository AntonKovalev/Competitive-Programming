#include <algorithm>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <unordered_map>
#include <cstdint>
#include <memory>
#include <array>

// https://www.topcoder.com/community/competitive-programming/tutorials/disjoint-set-data-structures/

using namespace std;

static int primeNumber = 0;

class Node;

typedef std::shared_ptr<Node> NodeSP;

class Node{

public:

Node()
: data(0)
, parent(0)
, rank(0)
{
}

int64_t data;
NodeSP parent;
int64_t rank;

}; // Node


//! Note that here data is the same as id of a node, 
//! so if you try to find a parent of a node, search for the node.data.
// This disjoint set class is implemented correctly, but is too slow for this problem.
// Therefore, it is not used in the solution below.
class DisjointSet{

public:

unordered_map<int64_t, NodeSP> map;

void makeSet(int64_t data)
{

    NodeSP node = make_shared<Node>();
    node->data = data;
    node->parent = node;
    map.insert({data, node});

}

bool unionSet(int64_t data1, int64_t data2)
{
    //cout << data1 << endl;
    NodeSP node1 = map.find(data1)->second;
    NodeSP node2 = map.find(data2)->second;

    NodeSP parent1 = findSet(node1);
    NodeSP parent2 = findSet(node2);

    // The same set, do nothing.
    if(parent1->data == parent2->data)
    {
        return false;
    }

    if(parent1->rank >= parent2->rank)
    {
        parent1->rank = (parent1->rank == parent2->rank) ? parent1->rank + 1 : parent2->rank;
        parent2->parent = parent1;
    }

    else
    {
        parent1->parent = parent2;
    }
    return true;

}

int64_t findSet(int64_t data)
{
    auto it = map.find(data);
    return findSet(it->second)->data;
}

NodeSP findSet(NodeSP node)
{
    NodeSP parent = node->parent;

    if(parent == node)
    {
        return parent;
    }

    node->parent = findSet(node->parent);
    return node->parent;
}

}; // DisjointSet

void sieveOfEratosthenes(vector<bool>& primes, 
                                int n)
{

fill( primes.begin(), primes.end(), true );
primes[0] = false;
primes[1] = false;

for(int i = 2; i < sqrt(n); ++i )   
{
    if( primes[i] )
    {
        for(int j = i*i; j <= n; j = j + i)
        {
            primes[j] = false;
        } 
    }
}
}

void print(bool v)
{
    if(v)
    {
        cout << primeNumber << endl;    
    }
    primeNumber++;
}

void printPrimes(vector<bool>& primes)
{
	for_each(primes.begin(), primes.end(), print);
}

//------------------------------------------------------------
// Implementation of union-find, see:
// https://www.geeksforgeeks.org/disjoint-set-data-structures/
//------------------------------------------------------------

// Finds the representative of the set that i
// is an element of.
int64_t find(vector<int64_t>& d, int64_t a) 
{
    // If i is the parent of itself
    if(d[a] == a) 
	 {
        // Then i is the representative 
        return a;
    }
	 // Recursively find the representative and move
    // each node up the tree, so that all nodes point directly to 
	 // the parent.
    return d[a] = find(d, d[a]);
}

bool join(vector<int64_t>& parent,
			 vector<int64_t>& rank, 
		    int64_t a, 
		    int64_t b) 
{
    a = find(parent, a);
    b = find(parent, b);
    if(a == b) return false;

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

int main()
{

int64_t cases, a, b, p, n;
cin >> n;
    vector<bool> primesBool;
    vector<int64_t> primes;
    primesBool.resize(1000000);
    sieveOfEratosthenes(primesBool, 1000000);

    for( int64_t i = 2; i < 1000000; ++i)
    {
        if(primesBool[i])
        {
            primes.push_back(i);
        }
    }

for( int cases = 0; cases < n; cases++)
{
	 scanf ("%ld %ld %ld",&a, &b, &p);
    int64_t diff = b - a;
if(diff == 0)
{
    cout << "Case #" << cases+1 << ": " << 1 <<endl;
}

else
{
    int64_t numberOfSets = b - a + 1;
	 const size_t SIZE = numberOfSets;

    vector<int64_t> parent(numberOfSets);
	 //array<int64_t,1000000> parent;
    vector<int64_t> rank(numberOfSets);

    for(int64_t i = 0; i <= b-a; i++) {
        parent[i] = i;
		  rank[i] = 0;
    }

    for(int64_t i = 0; i < primes.size(); ++i)
    {
        if(primes[i] >= p)// i is prime
        {
            int64_t currPrime = primes[i];
            int64_t ceiledVal = static_cast<int64_t>(ceil( static_cast<double>(a) /                                                                     static_cast<double>(currPrime) ) );

            // Put all numbers which have a common factor i in the same set.
            for(int64_t j = ceiledVal * currPrime; j <= b; j = j + currPrime)   
            {
					 if( j - currPrime - a >= 0 )
                {
                    if( join(parent, rank, j-a, j - currPrime - a) ) // Successfully merged two sets
                    {
                        numberOfSets--;
                    }
                }
            }
        }
    }
cout << "Case #" << cases+1 << ": " << numberOfSets <<endl;
}
}

return 0;
}