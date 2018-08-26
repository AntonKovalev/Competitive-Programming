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

bool myfunction (int i,int j) { return (i<j); }

int main()
{

vector <int> numbers;
int n;
scanf("%d",&n);
int total_cost=0;
for(int i = 0; i < n; ++i)
{
	int a;
	scanf("%d",&a);
	total_cost += a;
	numbers.push_back(a);
}
sort( numbers.begin(), numbers.end(), myfunction );
int rabatt = 0;
for(int j = n-3; j >= 0; j = j-3)
{
	if(j >= 0)
		rabatt += numbers.at(j);
}
printf("%d",total_cost - rabatt);
//cout << total_cost - rabatt;

return 0;
}