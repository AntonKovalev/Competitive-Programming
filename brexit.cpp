#include <iostream>
#include <vector>
#include <set>
#include <deque>          // std::deque

using namespace std;

typedef vector< set<int> > vvi;

int main()
{
int c,p,x,l;

//cin >> c >> p >> x >> l;
scanf("%d" "%d" "%d" "%d",&c,&p,&x,&l);
vector<int> n_neigh;
n_neigh.resize(c+1); // Are all ints initilized to 0???
vvi buckets;
buckets.resize(c+1);

for(int i = 1; i <= p; ++i)
{
	int a,b;
	//cin >> a >> b;
	scanf("%d" "%d", &a,&b);
	buckets.at(a).insert(b);
	buckets.at(b).insert(a);
	n_neigh.at(a) = n_neigh.at(a) + 1;
	n_neigh.at(b) = n_neigh.at(b) + 1;
}

deque<int> q;
q.push_back(l);
bool exit = false;
if(l == x)
	exit = true;
else
{
while( !q.empty() )
{
	/*if(exit)
	{	
		break;
	}*/
	auto elem = q.front();
	q.pop_front();
	
	for(auto it = (buckets.at(elem)).begin();
			 it != (buckets.at(elem)).end();
				++it )
	{
		(buckets.at(*it)).erase( elem );
		
		if( ( buckets.at(*it)).size() <= (n_neigh.at(*it)/2) ) // Double check the half
		{
			//Half of the neighbors is gone, this one will exit.
			q.push_back(*it);
		}
	}
	
			// My country and half or more of its neighbors are gone.
		if( (buckets.at(x)).size() <= (n_neigh.at(x)/2) )
		{
			exit = true;
			break;
		}
}
		// My country and half or more of its neighbors are gone.
		if( (buckets.at(x)).size() <= (n_neigh.at(x)/2) )
		{
			exit = true;
		}
}

if(exit)
	//cout << "leave";
	printf("%s","leave");
else
	printf("%s","stay");
	//cout << "stay";


return 0;
}