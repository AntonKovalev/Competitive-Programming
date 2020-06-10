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
#include <deque>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <sstream>      // std::stringstream
#include <stack>          // std::stack
#include <utility>      // std::pair
using namespace std;

const long MAX_V = 510;
typedef vector<long> vi;
vi p;
const int INF = numeric_limits<int>::max();

enum NodeErrorCode
{
	NOT_PRESENT = numeric_limits<int>::min(),
};

enum NodeState
{
	VISITED = numeric_limits<int>::max(),
	NOT_VISITED = numeric_limits<int>::min(),
};



//! Can only be used with positive node values.
template <class weight_type, class node_type>
struct OrderAccordingToIndex
{
	OrderAccordingToIndex(size_t size,
						  weight_type defaultValueWeight = NOT_PRESENT,
						  node_type   defaultValueNode = NOT_PRESENT )
	: m_neighbors( size, make_tuple( defaultValueWeight, defaultValueNode ) ) //! TODO: Be careful with this default value if node value is equal or greater than this.
	{}

	bool getNeighborWeightByNodeId(node_type n, weight_type& weight)
	{
		if( m_neighbors[n] )
		{
			weight = get<1>( m_neighbors[n] );
			return true;
		}
		return false;
	}

	void addNeighbor(node_type n, weight_type w = 0)
	{
		//Node node(n,w);
		this->m_neighbors[n] = make_tuple( n, w );
	}

	void removeNeighbor(node_type n)
	{
		m_neighbors.erase( m_neighbors.begin() + n );
	}

	void setDefaultNeighborValues(weight_type defaultValueWeight = NOT_PRESENT,
						  	  	  node_type   defaultValueNode = NOT_PRESENT )
	{
		for( auto&& i : m_neighbors )
		{
			i = make_tuple(defaultValueNode, defaultValueWeight);
		}
	}

	node_type getNeighborId(int idx) const
	{
		return get<0>(m_neighbors.at(idx));
	}

	node_type getNeighborWeightByIndex(int idx) const
	{
		return get<1>(m_neighbors.at(idx));
	}


	vector< tuple<node_type, weight_type> > m_neighbors;

};

template <class weight_type, class node_type>
struct OrderNotAccordingToIndex
{
	OrderNotAccordingToIndex(size_t size)
	: m_neighbors()
	{}

	bool getNeighborWeightByNodeId(node_type n, weight_type& weight)
	{
		for(typename vector<tuple<node_type, weight_type>>::iterator it = // use auto???
										m_neighbors.begin();
										it != m_neighbors.end();
														++it )
		{
			if( get<0>(*it) == n )
			{
				weight = get<1>(*it);
				return true;
			}
		}
		return false;
	}

	void pushNeighbor(node_type n, weight_type w = 0)
	{
		(this->m_neighbors).push_back( make_tuple( n, w ) ); //Maybe use emplace??? It will construct the element inside the container, instead of constructing it and then making a copy to pass to container.
	}

	void removeNeighbor(node_type n)
	{
		auto it = find (m_neighbors.begin(), m_neighbors.end(), n);
		m_neighbors.erase( it );
	}

	node_type getNeighborId(int idx) const
	{
		return get<0>(m_neighbors.at(idx));
	}

	node_type getNeighborWeightByIndex(int idx) const
	{
		return get<1>(m_neighbors.at(idx));
	}

	vector< tuple<node_type, weight_type> > m_neighbors;
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

		//! Use if we don't know number of neighbours. Should be used with
		//! OrderNotAccordingToIndex policy.
		/*Node(node_type id)
		: m_ID(id)
		//, m_neighbors()
		{

		}*/

		void setNodeID(node_type id)
		{
			m_ID = id;
		}

		//! Get the ID of this node.
		node_type getID() const
		{
			return m_ID;
		}
		// Useful e.g. in case node_type is a string.
		// It is the responsibility of the user to make sure that
		// no two of his nodes in the graph have the same idx.
		/*void setIndexInGraph(int idx)
		{
			m_idx = idx;
		}

		int getIndexInGraph(int idx)
		{
			return m_idx;
		}*/

		//! Add a neighbor with edge weight w, at a specific position in
		//! neighbour array.
		//void addNeighbor(node_type n, weight_type w);

		//! Push a neighbor with edge weight w into the neighbor array.
		//void pushNeighbor(node_type n, weight_type w);

		//! Returns number of neighbors for this node.
		size_t numberOfNeighbors() const;

		//! Check if this node has an edge to node2.
		bool isAdjacent( node_type node2 ) const;

		vector< tuple<node_type, weight_type> > getNeighbors() const;

	private:

		node_type m_ID;

		//int m_idx;
};

template<	class node_type,
			class weight_type,
			template <class N, class W> class neighborOrder >
vector< tuple<node_type, weight_type> >
Node<node_type, weight_type, neighborOrder>::getNeighbors() const
{
	return this->m_neighbors;
}

template< 	class node_type,
			class weight_type,
			template <class N,class W> class neighborOrder >
bool Node<node_type, weight_type, neighborOrder>::isAdjacent(node_type node2) const
{
	for(typename vector<tuple<node_type, weight_type>>::iterator it = //use auto???
										(this->m_neighbors).begin();
										it != (this->m_neighbors).end();
																++it )
	{
		//get_weight(this->m_neighbors,node2); //just to check if it will use policy's get_weight.
		if( get<0>(*it) == node2 )
			return true;
	}
	return false;
}

template< 	class node_type,
			class weight_type,
			template <class N,class W> class neighborOrder >
size_t Node<node_type, weight_type, neighborOrder>::numberOfNeighbors() const
{
	return (this->m_neighbors).size();
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
deque< nod > q;
q.push_back( graph[s] );//Maybe use emplace???
total++;
  while ( !q.empty() )
	{
		nod u = q.front();
		q.pop_front();
		//cout << "NODE: " << u.getID() << endl;
		auto neigh = u.getNeighbors();
		//cout << "Nr. of neighbors: " << neigh.size() << endl;
		//cout << " Node id:" << u.getID() << " nr. Of neighbors: " << u.getNeighbors().size() <<endl;
		for(int i = 0; i < neigh.size(); ++i )
		{
			int neighborID = u.getNeighborId(i);
			//cout << " neighbor: " << neighborID;

			if ( neighborID != NOT_PRESENT && dist[neighborID] == INF ) // neighborID != NOT_PRESENT is mine, not standard bfs.
			{
				q.push_back(graph[neighborID]);
				dist[neighborID] = dist[u.getID()] + 1;
				total++;
			}
		}
		//cout << endl;
	}
//print_ans(dist,total,n);
}

// inside int main()---no recursion


	//typedef Node<long, long, OrderNotAccordingToIndex> nod;
	//dist[ graph[s].getID() ] = 0;
	//long res[MAX_V][MAX_V];
	//deque< nod > q;

	typedef pair<int, int> ii; // In this chapter, we will frequently use these
	typedef vector<ii> vii; // three data type shortcuts. They may look cryptic
	//typedef vector<int> vi;
	// but they are useful in competitive programming
	// global variable, initially all values are set to UNVISITED
	void dfs(vector < Node<long, long, OrderNotAccordingToIndex> > &graph,
			vector<int> &dfs_num,
             int u)
	{
		typedef Node<long, long, OrderNotAccordingToIndex> nod;
		nod node = graph[u];
		dfs_num[node.getID()] = VISITED;
		auto neigh = node.getNeighbors();
		for( int i = 0; i < neigh.size(); ++i )
		{
			int neighborID = node.getNeighborId(i);
			if (dfs_num[neighborID] == NOT_VISITED)
			{
				dfs(graph, dfs_num, neighborID);
			}
		}
	}

	// Some problems may require Kahn's algorithm for toposort, see CP3.
	void dfs_toposort(map <string,  Node<string, long, OrderNotAccordingToIndex> >& graph,
					  //unordered_map<string, int> idxInGraph,
					  unordered_map<string, int>& dfs_num,
				   	  stack<string>& reverse_topo,
					  string u)
	{
		//cout << "enter" <<endl;
		typedef Node<string, long, OrderNotAccordingToIndex> nod;
		//int idx = idxInGraph[u];
		nod node = graph[u];
		dfs_num[node.getID()] = VISITED;
		auto neigh = node.getNeighbors();
		for( int i = 0; i < neigh.size(); ++i )
		{
			string neighborID = node.getNeighborId(i);
			if (dfs_num[neighborID] == NOT_VISITED)
			{
				dfs_toposort(graph /*, idxInGraph*/, dfs_num, reverse_topo, neighborID);
			}
		}
		reverse_topo.push(u); // topological sort, reversed.
		//cout << "Pushed!" <<endl;
	}

int main()
{
	//vector<int> dfs_num(n, NOT_VISITED);
	int n;
	unordered_set<char> delimeters = {':', ' '};
    string line, a, b;
    cin >> n;
    getline(cin, line);

    //Node<string, long, OrderNotAccordingToIndex> node_;
    typedef Node<string, long, OrderNotAccordingToIndex> node_type;
    map<string, node_type> graph;
	unordered_map<string, int>  dfs_num;

	   while(n--)
	   {
	      getline(cin, line);
	      stringstream ss(line);
	      ss >> a;
	      a.pop_back();
    	  auto it = graph.find(a);
    	  if (it == graph.end())
    	  {
    		  node_type nod(a);
    		  graph.insert ( std::pair<string,node_type>(a,nod) );

    	  }

		  dfs_num.insert(pair<string, int>(a,NOT_VISITED));
	      while(ss >> b)
	      {
	    	  auto it = graph.find(b);
	    	  if (it != graph.end())
	    	  {
	    		  graph[b].pushNeighbor(a);
	    	  }
	    	  else
	    	  {
	    		  node_type nod(b);
	    		  nod.pushNeighbor(a);
	    		  graph.insert ( std::pair<string,node_type>(b,nod) );
	    		  dfs_num.insert( std::pair<string, int>(b,NOT_VISITED) );
	    	  }

	          //adj[b].push_back(a);
	      }
	   }
	   getline(cin, line);
	   stack<string> reverse_topo;
	   dfs_toposort(graph, dfs_num, reverse_topo, line);
	   while(!reverse_topo.empty())
	   {
	           cout << reverse_topo.top() << '\n';
	           reverse_topo.pop();
	   }

/*vector < Node<long, long, OrderAccordingToIndex> > graph(10);
//graph.reserve(n);
for(long i = 0; i < 7; ++i)
{
	int id;
	cin >> id;
	//cout << "ID: " << id <<endl;
	int nrOfNeighbors;
	cin >> nrOfNeighbors;
	Node<long, long, OrderAccordingToIndex> node(id,10);
	for(int j = 0; j < nrOfNeighbors; j++)
	{
		//cout << "Working! 2 ";
		int neigh;
		cin >> neigh;
		node.addNeighbor(neigh);
		//cout << ",neigh : " << neigh  << " ";;
	}
	//cout << endl;
	graph[id] = node; //Maybe use emplace???

}

bfs(graph, 4, 10);*/

return 0;
}
