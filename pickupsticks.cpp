#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef pair<int, int> ii;      // In this chapter, we will frequently use these
typedef vector<ii> vii;      // three data type shortcuts. They may look cryptic
typedef vector<int> vi;   // but shortcuts are useful in competitive programming

#define UNVISITED -1 // normal DFS, do not change this with other values (other than 0), because we usually use memset with conjunction with DFS_WHITE
#define VISITED 1

vector<vi> AdjList;
vi dfs_num; // this variable has to be global, we cannot put it in recursion
vi topoSort;             // global vector to store the toposort in reverse order
vi cycle;
bool noCycle;

void topo(int u,int i) 
{  
  dfs_num[u] = VISITED;
  cycle[u] = i;
  for (int j = 0; j < (int)AdjList[u].size(); j++) 
  {
    int v = AdjList[u][j];
    if (dfs_num[v] == UNVISITED)
	{
      topo(v,i);
	}
	else if( dfs_num[v] == VISITED)
	{
		noCycle = false;
		return;
	}
  }
topoSort.push_back(u); 
dfs_num[u] = -5;
} 

int main ()
{
int n,m;
noCycle = true;
cin >> n >> m;
AdjList.assign(n+1,vi());
dfs_num.assign(n+1,UNVISITED);
cycle.assign(n+1, 0);	
int a,b;

/*if(n == 1 && m==1) // only 1 stick in the input.
{
	cout << "1";
	return 0;
}*/

for(int i = 0; i < m; ++i)
{
	cin >> a >> b;
	/*pair<int,int> par;
	par = make_pair(b,0);*/
	AdjList[a].push_back( b );
}	

for(int i = 1; i <= n; ++i)
{
	if(dfs_num[i] == UNVISITED)
	{
		topo(i,i);
	}
	
	if(!noCycle)
	{
		break;
	}
}

if(!noCycle)
{
	cout << "IMPOSSIBLE";
}
else
{
	for (int i = (int)topoSort.size() - 1; i >= 0; i--) // read backwards
	{
		if(i != 0)
			printf("%d\n", topoSort[i]);
		else
			printf("%d", topoSort[i]);
	}
}

return 0;
}