#include<iostream>
#include<stdlib.h>
#include<vector>
#include<cmath>
#include <iomanip>

using namespace std;

const double areaA1 = 0.5;
const double widthA2 = 0.4204482076;
const double lengthA2 = 0.5946035575;
const double widthA1 = widthA2 * 2;
const double lengthA1 = lengthA2;

#define loop(x,m) for(int x = 0; x < m; ++x)

struct paper
{
paper(int length, int width)
: m_length(length)
, m_width(width)
{
}
int m_length;
int m_width;
};

double solve( vector<int> numberOfArcs )
{
	double total_area = 0;	
	double previous_area = areaA1;
	vector<int> neededArcs;
	double rest(0);
	loop( i, numberOfArcs.size() )
	{
		double area = previous_area/2;
		previous_area = area;
		rest = 0.5 - total_area; // when rest = 0 we are done -> jump out.
		
		int nrOfArcs = rest/area; // we need at least this many arcs of size area.
		int availableArcs = numberOfArcs[i];
		if( availableArcs >= nrOfArcs )
		{
			neededArcs.push_back(nrOfArcs);
			rest = 0;
			break;
		}
		neededArcs.push_back(numberOfArcs[i]);
		total_area = total_area + numberOfArcs[i] * area;
	}
	
	if( rest != 0)
	{
		return -1;
	}
	else
	{
	double previous_height = lengthA1;
	double previous_width = widthA1;
	double tape = 0;
		loop( i, neededArcs.size() )
		{
		double current_height;
		double current_width;
			if( (i+2) % 2 == 0)
			{
				current_height = previous_height;
				current_width = previous_width/2;
			}
			else
			{
				current_height = previous_height/2;
				current_width = previous_width;
			}
			tape = tape + (current_height*2 + current_width*2) * neededArcs[i];
			
				previous_height = current_height;
				previous_width = current_width;
		}
		return ( tape - widthA1*2 - lengthA1*2 )/2;
	}
}

int main()
{
int n;
cin >> n;
vector<paper> arcs;
vector<int> numberOfArcs;
loop(i,n-1)
{
	int arcs;
	cin >> arcs;
	numberOfArcs.push_back(arcs);
}
	double sol = solve(numberOfArcs);
	if( sol < 0 )
	{
		cout << "impossible";
	}
	else
	{
		cout << std::setprecision(10) << sol;
	}
	return 0;
}