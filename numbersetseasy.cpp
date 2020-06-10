#include <algorithm>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <unordered_map>
#include <cstdint>
#include <memory>

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
int rank;

}; // Node


//! Note that here data is the same as id of a node, 
//! so if you try to find a parent of a node, search for the node.data.
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

int main()
{
int cases, a, b, p, n;
cin >> n;
for( int cases = 0; cases < n; cases++)
{
	cin >> a >> b >> p;
	vector<bool> primes;
	int diff = b - a;
	primes.resize(diff);
	sieveOfEratosthenes(primes, diff);
	DisjointSet ds;
	int numberOfSets = b - a + 1;
	// Make each prime an own set.
	for(int i = a; i <= b; ++i)
	{
			ds.makeSet(i);
	}
	
	for(int i = p; i < primes.size(); ++i)
	{
		if(primes[i])// i is prime
		{
			int ceiledVal = static_cast<int>(ceil( static_cast<double>(a) / 							  										static_cast<double>(i) ) );

			// Put all numbers which have a common factor i in the same set.
			for(int j = ceiledVal * i; j <= b; j = j + i)	
			{
				if(j != ceiledVal * i)
				{
					bool result = ds.unionSet(j, j - i);
					if(result) // Successfully merged two sets
					{
						numberOfSets--;
					}
				}
			}
		}
	}
cout << "Case #" << cases+1 << ": " << numberOfSets <<endl;
}
return 0;
}