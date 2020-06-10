#include <algorithm>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <unordered_map>
#include <cstdint>
#include <memory>
#include <array>
#include <string>
#include <sstream> 

using namespace std;

// Fun fact: this code will NOT pass if we use cout instead of printf...

//------------------------------------------------------------
// Implementation of union-find, see:
// https://www.geeksforgeeks.org/disjoint-set-data-structures/
//------------------------------------------------------------

// Finds the representative of the set that i
// is an element of.
int find(vector<int>& parent, int a) 
{
    // If i is the parent of itself
    if(parent[a] == a) 
	 {
        // Then i is the representative 
        return a;
    }
	 // Recursively find the representative and move
    // each node up the tree, so that all nodes point directly to 
	 // the parent.
    return parent[a] = find(parent, parent[a]);
}

bool join(vector<int>& parent,
			 vector<int>& rank, 
		    int a, 
		    int b) 
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

int n, q;

cin >> n >> q;

vector<int> parent(n);
vector<int> rank(n);
for(int i = 0; i < n; ++i)
{
	parent[i] = i;
	rank[i] = 0;
}

for(int i = 0; i < q; ++i)
{

char c;
int q1, q2;
scanf(" %c %d %d", &c, &q1, &q2);
	if(c == '=') 
	{
		join(parent, rank, q1, q2);
	}
	else if(c == '?')
	{
		if(find(parent, q1) == find(parent, q2))
		{
			printf("yes\n");		
		}
		else
		{
			printf("no\n");		
		}
	}
}

return 0;
}