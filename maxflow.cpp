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
// ID of the node, a vector of all adjacent nodes and corresponding weights.
typedef tuple<long,vector< tuple<long,long> > > node;
//typedef vector< node > graph;

template <class weight_type, class node_type>
struct OrderAccordingToIndex
{
	/*template <	class weight_type, 
				class node_type>*/
	weight_type get_weight(vector< tuple<node_type, weight_type> > neighbours,
							node_type n)
	{
		return get<1>( neighbours[n] );
	}
	
}; 

template <class weight_type, class node_type>
struct OrderNotAccordingToIndex
{
	/*template <	class weight_type, 
				class node_type>*/
	weight_type get_weight(vector< tuple<node_type, weight_type> > neighbours,
							node_type n)
	{
		for(typename vector<tuple<node_type, weight_type>>::iterator it = // use auto???
										neighbours.begin();
										it != neighbours.end();
														++it )
		{
			if( get<0>(*it) == n )
				return get<1>(*it);
		}
	}
}; 

//! Supports only numerical values for node_type, i.e. no char, string etc.
template< 	class node_type, 
			class weight_type, 
			template <class N,class W> class neighborOrder >
class Node : public neighborOrder<node_type, weight_type>
{
	public:
		
	Node() = default;
	
	//! Use if we know number of neighbours. Should be used with
	//! OrderAccordingToIndex policy.
	Node(node_type id, size_t sz)
	: m_ID(id)
	, m_neighbours(sz)
	{
		
	}
	
	//! Use if we don't know number of neighbours. Should be used with
	//! OrderNotAccordingToIndex policy.
	Node(node_type id)
	: m_ID(id)
	, m_neighbours()
	{
		
	}
	
	void setNodeID(node_type id)
	{
		m_ID = id;
	}
	
	//! Get the ID of this node.
	node_type getID(){ return m_ID; }
	
	//! Add a neighbor with edge weight w, at a specific position in
	//! neighbour array.
	void add_neighbour(node_type n, weight_type w);
	
	//! Push a neighbor with edge weight w longo the neighbor array.
	void push_neighbour(node_type n, weight_type w);
	
	//! Get weight of the edge connected to node n.
	/*weight_type get_weight( node_type n );*/
	
	//! Get weight of the edge connected to node n.
	/*weight_type get_weight( node_type n )
	{
		return 
	}*/
	
	//! Returns number of neighbors for this node. 
	size_t number_of_neighbours() const;
	
	//! Check if this node has an edge to node2.
	bool is_adjacent( node_type node2 ) const;
	
	vector< tuple<node_type, weight_type> > getNeighbors();
	
	private:
	node_type m_ID;	
	vector< tuple<node_type, weight_type> > m_neighbours;
};

template<	class node_type,
			class weight_type,
			template <class N, class W> class neighborOrder >
vector< tuple<node_type, weight_type> >
Node<node_type, weight_type, neighborOrder>::getNeighbors()
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
		//get_weight(this->m_neighbours,node2); //just to check if it will use policy's get_weight.
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
													

//! TODO: Decide by policy, if we use a neighbor array 
//! where the index of the node is the same as the ID or not.
//! Here: do we want to search through the array, to find the 
//! weight of the edge to node?
/*template< 	class node_type, 
			class weight_type, 
			template <class> class neighborOrder >
weight_type Node<node_type, weight_type, size, neighborOrder>::get_weight(
													node_type n)
{
	return get<1>(this->m_neighbours[n]);
}*/

//! This function adds a neighbor at the specified index in the
//! neighbor array. If you only want to push the new neighbor node
//! longo the neighbor set, see push_neighbour. Should be merged with the
//! corresponding policy of get_weight?
template< 	class node_type, 
			class weight_type, 
			template <class N,class W> class neighborOrder >
void Node< node_type, weight_type, neighborOrder >::add_neighbour( 
									node_type n, weight_type w )
{
	//Node node(n,w);
	this->m_neighbours[n] = make_tuple( n, w );
}

template< 	class node_type, 
			class weight_type, 
			template <class N,class W> class neighborOrder >
void Node< node_type, weight_type, neighborOrder>::push_neighbour( 
									node_type n, weight_type w )
{
	(this->m_neighbours).push_back( make_tuple( n, w ) ); //Maybe use emplace??? It will construct the element inside the container, instead of constructing it and then making a copy to pass to container.
}


const long MAX_V = 510;
long res[MAX_V][MAX_V], mf, f; // global variables
long g[MAX_V][MAX_V];
typedef vector<long> vi;
vi p;
const long long INF = numeric_limits<long long>::max();

void print_ans(vector<int>& parent, int total, long n)
{
printf("%d %d ",n,mf);
//For min cut below.
int total_edges = 0;
for(int i = 0; i < n; ++i )
{
	for(int j = 0; j < n; ++j )
	{
		if( g[i][j] - res[i][j] > 0 )
		{
			total_edges++;
		}
	}	
}

printf("%d\n",total_edges);
for(int i = 0; i < n; ++i )
{
	for(int j = 0; j < n; ++j )
	{
		if( g[i][j] - res[i][j] > 0 )
		{
			total_edges++;
			printf("%d %d %d \n",i,j,g[i][j] - res[i][j]);
		}
	}	
}
}

//! BFS
void bfs( vector < Node<long, long, OrderNotAccordingToIndex> > &graph, 
			long s, long n )
{
	
int total = 0;
typedef Node<long, long, OrderNotAccordingToIndex> nod;
vector<int> dist(n, 0); 
dist[s] = 1; 
deque< nod > q; 
q.push_back(graph[s]);//Maybe use emplace???
total++;
  while (!q.empty()) 
{
	nod u = q.front(); 
	q.pop_front();
	auto neigh = u.getNeighbors();
	/*for (auto it = neigh.begin();
			  it != neigh.end();
			  ++it )*/
	for(int i = 0; i < n; ++i )
	{
		if ( res[u.getID()][i] > 0 && dist[i] == 0 )
		{
			q.push_back(graph[i]);
			dist[i] = 1;
			total++;
		}
	}
}
print_ans(dist,total,n);
}

void augment(long s, long v, long minEdge) 
{
	if (v == s) 
	{ 
		f = minEdge; 
		return; 
	} 
	else if (p[v] != -1) 
	{ 
		augment(s, p[v], min(minEdge, res[p[v]][v]) );
		res[p[v]][v] -= f; 
		res[v][p[v]] += f; 
	} 
}

int main()
{
memset(res, 0, sizeof res);
long n,m,s,t;
cin >> n >> m >> s >> t;

vector < Node<long, long, OrderNotAccordingToIndex> > graph;
//graph.reserve(n);
for(long i = 0; i < n; ++i)
{
	Node<long, long, OrderNotAccordingToIndex> node(i);
	graph.push_back(node); //Maybe use emplace???
}

for(long i = 0; i < m; ++i )
{
	int u,v,w = 0;
	//cin >> u >> v >> w;
	scanf("%d %d %d",&u,&v,&w);
	graph[u].push_neighbour(v,w);
	res[u][v] = w;
	g[u][v] = w;
}

/*for (long i = 0; i < graph.size(); i++)
{
	//cout << "For node " << i <<": "<<endl;
	auto vec = graph[i].getNeighbors();
	for(long j = 0; j < graph[i].number_of_neighbours(); j++)
	{
		//cout << get<0>(vec[j]) << endl;
	}
}*/

//! Min Cut starts here!!!
typedef Node<long, long, OrderNotAccordingToIndex> nod;
mf = 0; // mf stands for max_flow
while (1) { // O(VE^2) (actually O(V^3 E) Edmonds Karp’s algorithm
f = 0;
// run BFS, compare with the original BFS shown in Section 4.2.2

vector<int> dist(MAX_V, 0); 
dist[s] = 1; 
deque< nod > q; 
q.push_back(graph[s]);//Maybe use emplace???
p.assign(MAX_V, -1); // record the BFS spanning tree, from s to t!
while (!q.empty()) 
{
	nod u = q.front(); 
	q.pop_front();
	if ( u.getID() == t ) 
		break; // immediately stop BFS if we already reach sink t
	auto neigh = u.getNeighbors();
	/*for (auto it = neigh.begin();
			  it != neigh.end();
			  ++it )*/
	
for(int i = 0; i < n; ++i)
	{
		if ( res[u.getID()][i] > 0 && dist[i] == 0 )
		{
			dist[i] = 1;
			q.push_back(graph[i]);
			p[i] = u.getID(); 
		}
	}
}
augment(s, t, INF); 
if (f == 0) 
	break; 
mf += f;
}

bfs(graph, s,n);
//printf("%d\n", mf); // this is the max flow value

return 0;
}