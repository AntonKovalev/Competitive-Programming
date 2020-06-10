//============================================================================
// Name        : algorithms.cpp
// Author      : Anton Kovalev
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <vector>
#include <iostream>
#include <tuple>
#include <limits>
#include <deque>          // std::deque
//#include <queue>          // std::queue
#include <cstdio>
#include <stdio.h>
#include <string.h>

using namespace std;

enum NodeErrorCode
{
	NOT_PRESENT = numeric_limits<int>::min(),
};

const long MAX_V = 510;
long mf, f; // global variables
typedef vector<long> vi;
vi p;
const int INF = numeric_limits<int>::max();

//! Can only be used with positive node values.
template <class weight_type, class node_type>
struct OrderAccordingToIndex
{
	OrderAccordingToIndex(size_t size,
						  weight_type defaultValueWeight = NOT_PRESENT,
						  node_type   defaultValueNode = NOT_PRESENT )
	: m_neighbours( size, make_tuple( defaultValueWeight, defaultValueNode ) ) //! TODO: Be careful with this default value if node value is equal or greater than this.
	{}

	bool getNeighborWeight(node_type n, weight_type& weight)
	{
		if( m_neighbours[n] )
		{
			weight = get<1>( m_neighbours[n] );
			return true;
		}

		return false;
	}

	void addNeigbor(node_type n, weight_type w = 0)
	{
		//Node node(n,w);
		this->m_neighbours[n] = make_tuple( n, w );
	}

	void removeNeighbour(node_type n)
	{
		m_neighbours.erase( m_neighbours.begin() + n );
	}

	void setDefaultNeighborValues(weight_type defaultValueWeight = NOT_PRESENT,
						  	  	  node_type   defaultValueNode = NOT_PRESENT )
	{
		for( auto&& i : m_neighbours )
		{
			i = make_tuple(defaultValueNode, defaultValueWeight);
		}
	}

	node_type getNeighborId(int idx) const
	{
		return get<0>(m_neighbours[idx]);
	}

	vector< tuple<node_type, weight_type> > m_neighbours;

};

template <class weight_type, class node_type>
struct OrderNotAccordingToIndex
{
	OrderNotAccordingToIndex(size_t size)
	: m_neighbours()
	{}

	bool getNeighborWeight(node_type n, weight_type& weight)
	{
		for(typename vector<tuple<node_type, weight_type>>::iterator it = // use auto???
										m_neighbours.begin();
										it != m_neighbours.end();
														++it )
		{
			if( get<0>(*it) == n )
			{
				weight = get<1>(*it);
			}
		}
		return false;
	}

	void push_neighbour(node_type n, weight_type w = 0)
	{
		(this->m_neighbours).push_back( make_tuple( n, w ) ); //Maybe use emplace??? It will construct the element inside the container, instead of constructing it and then making a copy to pass to container.
	}

	void removeNeighbour(node_type n)
	{
		auto it = find (m_neighbours.begin(), m_neighbours.end(), n);
		m_neighbours.erase( it );
	}

	node_type getNeighborId(int idx) const
	{
		return get<0>(m_neighbours[idx]);
	}

	vector< tuple<node_type, weight_type> > m_neighbours;
};

//! Supports only numerical values for node_type, i.e. no char, string etc.
template< 	class node_type,
			class weight_type,
			template <class N,class W> class neighborOrder >
class Node : public neighborOrder< weight_type, node_type>
{
	public:

		Node()
		: neighborOrder< weight_type, node_type>(0)
		, m_ID(0)
		{

		}

		Node(node_type id, size_t sz = 0)
		: neighborOrder< weight_type, node_type>(sz)
		, m_ID(id)
		{

		}

		void setNodeID(node_type id)
		{
			m_ID = id;
		}

		//! Get the ID of this node.
		node_type getID(){ return m_ID; }

		//! Returns number of neighbors for this node.
		size_t number_of_neighbours() const;

		//! Check if this node has an edge to node2.
		bool is_adjacent( node_type node2 ) const;

		vector< tuple<node_type, weight_type> > getNeighbors() const;

	private:

		node_type m_ID;
};

template<	class node_type,
			class weight_type,
			template <class N, class W> class neighborOrder >
vector< tuple<node_type, weight_type> >
Node<node_type, weight_type, neighborOrder>::getNeighbors() const
{
	return this->m_neighbours;
}

template< 	class node_type,
			class weight_type,
			template <class N,class W> class neighborOrder >
bool Node<node_type, weight_type, neighborOrder>::is_adjacent(node_type node2) const
{
	for(typename vector<tuple<node_type, weight_type>>::iterator it = //use auto???
										(this->m_neighbours).begin();
										it != (this->m_neighbours).end();
																++it )
	{
		if( get<0>(*it) == node2 )
			return true;
	}
	return false;
}

template< 	class node_type,
			class weight_type,
			template <class N,class W> class neighborOrder >
size_t Node<node_type, weight_type, neighborOrder>::number_of_neighbours() const
{
	return (this->m_neighbours).size();
}

void print_ans(vector<int>& parent, int total, long n)
{

	for( int i = 0; i < parent.size(); ++i)
	{
		cout << "Distance to node " << i << " is " << parent[i] << endl;
	}

}

//! BFS
void bfs( vector < Node<long, long, OrderNotAccordingToIndex> > &graph,
			long s, long n, vector<int> &dist )
{

int total = 0;
typedef Node<long, long, OrderNotAccordingToIndex> nod;
dist[ graph[s].getID() ] = 0;
long res[MAX_V][MAX_V];
deque< nod > q;
q.push_back( graph[s] );//Maybe use emplace???
total++;
  while ( !q.empty() )
	{
		nod u = q.front();
		q.pop_front();
		auto neigh = u.getNeighbors();
		for(int i = 0; i < neigh.size(); ++i )
		{
			int neighborID = u.getNeighborId(i);

			if ( neighborID != NOT_PRESENT && dist[neighborID] == INF )
			{
				q.push_back(graph[neighborID]);
				dist[neighborID] = dist[u.getID()] + 1;
				total++;
			}
		}
	}
}

void solve()
{
	vector < Node<long, long, OrderNotAccordingToIndex> > graph;
	int r;
	int c;
	cin >> r >> c;
	string row;
	int id = 0;
	getline( cin, row);
	for(int i = 0; i < r; ++i)
	{
		getline( cin, row);
		for(int j = 0; j < c; ++j)
		{
			Node<long, long, OrderNotAccordingToIndex> node( id );
			int steps = row[j] - '0';
			if( steps != 0)
			{
				if( j - steps >= 0  ) // Left
				{
					node.push_neighbour( (i * c) + j - steps);
				}
				if( j + steps < c ) // Right
				{
					node.push_neighbour( (i * c) + j + steps);
				}
				if( i - steps >= 0 ) // Up
				{
					node.push_neighbour( id - c * steps );
				}
			    if( i + steps < r ) // Down
				{
					node.push_neighbour( id + c * steps );
				}
			}
			graph.push_back(node);
			++id;
		}
	}
	vector<int> dist(c*r, INF);
	bfs(graph, 0, c*r, dist);

	if(dist[c*r-1] == INF)
		cout << -1;
	else
		cout << dist[c*r - 1];
}

int main()
{

solve();

return 0;
}
