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
						  node_type defaultValueNode = NOT_PRESENT)
		: m_neighbors(size, make_tuple(defaultValueWeight, defaultValueNode)) //! TODO: Be careful with this default value if node value is equal or greater than this.
	{
	}

	bool getNeighborWeightByNodeId(node_type n, weight_type &weight)
	{
		if (m_neighbors[n])
		{
			weight = get<1>(m_neighbors[n]);
			return true;
		}
		return false;
	}

	void addNeighbor(node_type n, weight_type w = 0)
	{
		//Node node(n,w);
		this->m_neighbors[n] = make_tuple(n, w);
	}

	void removeNeighbor(node_type n)
	{
		m_neighbors.erase(m_neighbors.begin() + n);
	}

	void setDefaultNeighborValues(weight_type defaultValueWeight = NOT_PRESENT,
								  node_type defaultValueNode = NOT_PRESENT)
	{
		for (auto &&i : m_neighbors)
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

	vector<tuple<node_type, weight_type>> m_neighbors;
};

template <class weight_type, class node_type>
struct OrderNotAccordingToIndex
{
	OrderNotAccordingToIndex(size_t size)
		: m_neighbors()
	{
	}

	bool getNeighborWeightByNodeId(node_type n, weight_type &weight)
	{
		for (typename vector<tuple<node_type, weight_type>>::iterator it = // use auto???
			 m_neighbors.begin();
			 it != m_neighbors.end();
			 ++it)
		{
			if (get<0>(*it) == n)
			{
				weight = get<1>(*it);
				return true;
			}
		}
		return false;
	}

	void pushNeighbor(node_type n, weight_type w = 0)
	{
		(this->m_neighbors).push_back(make_tuple(n, w)); //Maybe use emplace??? It will construct the element inside the container, instead of constructing it and then making a copy to pass to container.
	}

	void removeNeighbor(node_type n)
	{
		auto it = find(m_neighbors.begin(), m_neighbors.end(), n);
		m_neighbors.erase(it);
	}

	node_type getNeighborId(int idx) const
	{
		return get<0>(m_neighbors.at(idx));
	}

	node_type getNeighborWeightByIndex(int idx) const
	{
		return get<1>(m_neighbors.at(idx));
	}

	vector<tuple<node_type, weight_type>> m_neighbors;
};

//! Supports only numerical values for node_type, i.e. no char, string etc.
template <class node_type,
		  class weight_type,
		  template <class N, class W> class neighborOrder>
class Node : public neighborOrder<weight_type, node_type>
{
public:
	Node()
		: neighborOrder<weight_type, node_type>(0), m_ID(0)
	{
	}

	Node(node_type id, size_t sz = 0)
		: neighborOrder<weight_type, node_type>(sz), m_ID(id)
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

	//! Returns number of neighbors for this node.
	size_t numberOfNeighbors() const;

	//! Check if this node has an edge to node2.
	bool isAdjacent(node_type node2) const;

	vector<tuple<node_type, weight_type>> getNeighbors() const;

private:
	node_type m_ID;
};

template <class node_type,
		  class weight_type,
		  template <class N, class W> class neighborOrder>
vector<tuple<node_type, weight_type>>
Node<node_type, weight_type, neighborOrder>::getNeighbors() const
{
	return this->m_neighbors;
}

template <class node_type,
		  class weight_type,
		  template <class N, class W> class neighborOrder>
bool Node<node_type, weight_type, neighborOrder>::isAdjacent(node_type node2) const
{
	for (typename vector<tuple<node_type, weight_type>>::iterator it = //use auto???
		 (this->m_neighbors).begin();
		 it != (this->m_neighbors).end();
		 ++it)
	{
		//get_weight(this->m_neighbors,node2); //just to check if it will use policy's get_weight.
		if (get<0>(*it) == node2)
			return true;
	}
	return false;
}

template <class node_type,
		  class weight_type,
		  template <class N, class W> class neighborOrder>
size_t Node<node_type, weight_type, neighborOrder>::numberOfNeighbors() const
{
	return (this->m_neighbors).size();
}

void print_ans(vector<int> &parent, int total, long n)
{
	for (int i = 0; i < parent.size(); ++i)
	{
		cout << "Distance to node " << i << " is " << parent[i] << endl;
	}
}

typedef vector<Node<long, long, OrderNotAccordingToIndex>> GraphNotAccordingToIndex;

//! BFS
void bfs(GraphNotAccordingToIndex &graph,
		 long s,
		 long n,
		 vector<int> &dist)
{
	int total = 0;
	typedef Node<long, long, OrderNotAccordingToIndex> nod;
	dist[graph[s].getID()] = 0;
	deque<nod> q;
	q.push_back(graph[s]);
	total++;
	while (!q.empty())
	{
		nod u = q.front();
		q.pop_front();
		auto neigh = u.getNeighbors();
		for (int i = 0; i < neigh.size(); ++i)
		{
			int neighborID = u.getNeighborId(i);

			if (neighborID != NOT_PRESENT && dist[neighborID] == INF) // neighborID != NOT_PRESENT is mine, not standard bfs.
			{
				q.push_back(graph[neighborID]);
				dist[neighborID] = dist[u.getID()] + 1;
				total++;
			}
		}
	}
	//print_ans(dist,total,n);
}
void dfs(GraphNotAccordingToIndex &graph,
		 vector<int> &dfs_num,
		 int u)
{
	typedef Node<long, long, OrderNotAccordingToIndex> nod;
	nod node = graph[u];
	dfs_num[node.getID()] = VISITED;
	auto neigh = node.getNeighbors();
	for (int i = 0; i < neigh.size(); ++i)
	{
		int neighborID = node.getNeighborId(i);
		if (dfs_num[neighborID] == NOT_VISITED)
		{
			dfs(graph, dfs_num, neighborID);
		}
	}
}

// Some problems may require Kahn's algorithm for toposort, see CP3.
void dfs_toposort(map<string, Node<string, long, OrderNotAccordingToIndex>> &graph,
				  unordered_map<string, int> &dfs_num,
				  stack<string> &reverse_topo,
				  string u)
{
	typedef Node<string, long, OrderNotAccordingToIndex> NodeT;
	NodeT node = graph[u];
	dfs_num[node.getID()] = VISITED;
	auto neigh = node.getNeighbors();
	for (int i = 0; i < neigh.size(); ++i)
	{
		string neighborID = node.getNeighborId(i);
		if (dfs_num[neighborID] == NOT_VISITED)
		{
			dfs_toposort(graph, dfs_num, reverse_topo, neighborID);
		}
	}
	reverse_topo.push(u); // topological sort, reversed.
}

using NodeT = Node<long, long, OrderNotAccordingToIndex>;

void dijkstra(int s, int nrOfNodes, vector<NodeT>& graph, vector<int>& dist)
{
	//vi dist(nrOfNodes, INF); // INF should be something like 1B to avoid overflow!
	dist[s] = 0;
	typedef tuple<int,int> ii;
	priority_queue<ii, vector<ii>, greater<ii>> pq;
	pq.push(ii(0, s)); //(distance, "to vertex from source")
	while (!pq.empty())
	{
		ii front = pq.top();
		pq.pop(); // greedy: get shortest unvisited vertex
		int d = get<0>(front);
		int u = get<1>(front);
		if (d > dist[u])
			continue; // this is a very important check

		auto neighbors = graph[u].getNeighbors();
		for (int j = 0; j < neighbors.size(); j++)
		{
			auto v = neighbors[j]; // all outgoing edges from u
			int weight, vertex;
			tie(vertex, weight) = v; // weight from u to vertex
			if (dist[u] + weight < dist[vertex])
			{
				dist[vertex] = dist[u] + weight;// relax operation
				pq.push(ii(dist[vertex], vertex));
			}
		}
	}
}

int dijkstra2(	int s, 
				int goal,
				vector<NodeT>& graph,
				vector<int>& dist,
                vector<vector<pair<int, int>>>& parent,
                vector<bool>& visited)
{
	int shortestFromEntranceToPeak = 0;
	//vi dist(nrOfNodes, INF); // INF should be something like 1B to avoid overflow!
	dist[s] = 0;
	typedef tuple<int,int> ii;
	priority_queue<ii, vector<ii>, greater<ii>> pq;
	pq.push(ii(0, s)); //(distance, "to vertex from source")
	while (!pq.empty())
	{
		ii front = pq.top();
		pq.pop(); // greedy: get shortest unvisited vertex
		int d = get<0>(front);
		int u = get<1>(front);
		if (d > dist[u])
			continue; // this is a very important check

		auto neighbors = graph[u].getNeighbors();
		for (int j = 0; j < neighbors.size(); j++)
		{
			auto v = neighbors[j]; // all outgoing edges from u
			int weight, vertex;
			tie(vertex, weight) = v; // weight from u to vertex
			if ( dist[u] + weight == dist[vertex] )
			{
                //cout << "vertex: " << vertex << " parent: " << u << endl;
                parent[vertex].push_back(pair<int,int>(u,weight));
                
            }
            else if ( dist[u] + weight < dist[vertex] )
			{
                /*if(vertex == 7)
                {
                    cout << "vertex: " << vertex << " parent: " << u << " weight " << weight <<  endl; 
                }*/
                parent[vertex].clear();
                parent[vertex].push_back(pair<int,int>(u,weight));

                dist[vertex] = dist[u] + weight;// relax operation
				pq.push(ii(dist[vertex], vertex));
            }
		}
	}

    /*for(int i = parent.size()-1; i >= 0; --i)
    {
        for(int j = 0; j < parent[i].size(); ++j)
        {
            cout << "Node " << i << " has parent: " << parent[i][j].first << " weight: " << parent[i][j].second << endl;
        }
    }*/
    int node = goal;
    int cost = 0;
    deque<int> q;
    q.push_back(node);
    while(!q.empty())
    {
        node = q.front();
		q.pop_front();
        for(int i = 0; i < parent[node].size(); ++i)
        {
            int vertex = parent[node][i].first;
            int weight = parent[node][i].second;
            cost += weight;
            if(!visited[vertex]) // we have not visited vertex yet.
            {
                visited[vertex] = true;
                q.push_back(vertex);
            }
        }
    }
    return cost;
}


int main()
{
	int p, t;
	cin >> p >> t;
	vector<NodeT> graph(p);
    //parentList[i] = ett par {grannar, kostnad hittills}
    vector<vector<pair<int, int>>> parentList(p);
    vector<bool> visited(p, false);
	for(int i = 0; i < t; ++i)
	{
		int u,v,l;
		cin >> u >> v >> l;
		graph[u].pushNeighbor(v,l);
        graph[v].pushNeighbor(u,l);
	}
	vector<int> dist(p, 1000000000);
	int ans = dijkstra2(0, p-1, graph, dist, parentList, visited);
	cout << 2*ans ;
	return 0;
}
