#include<iostream>
#include<stdlib.h>
#include<vector>
#include<cmath>
#include<set>
#include <stdio.h>
#include <unordered_map>
using namespace std;

#define loop(i,n) for(int i = 0; i < n; ++i)

int main()
{

int ans = 0;
int jill = 0;
int jack = 0;
scanf("%d%d", &jill, &jack);
while(jill != 0 && jack != 0)
{
	int firstNumbers[1000005];
	ans = 0;
	loop(i, jill)
	{
		int cd;
		scanf("%d", &cd);
		firstNumbers[i] = cd;
	}

	int idx = 0;
	for(int i = 0; i < jack; ++i)
	{
		int cd;
		scanf("%d", &cd);

		if(idx < jill && cd == firstNumbers[idx])
		{
			ans++;
			idx++;
		}
		else if(idx < jill && cd > firstNumbers[idx])
		{
			while( idx < jill && cd >= firstNumbers[idx] )
			{
				if(cd == firstNumbers[idx])
				{
					ans++;
					idx++;
					break;
				}
				else
				{
					idx++;
				}
			}
		}
	}

	printf("%d\n", ans);
	scanf("%d%d", &jill, &jack);
}

return 0;
}