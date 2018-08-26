#include <iostream>
#include <vector>
#include <algorithm>    // std::max

using namespace std;

void calculate_maximum_subarray(int &n, int &m, vector<int> &array)
{
	int left, right = 0;
	int maximum = m;
	bool left_right = false;
	for(int i = 0; i < n; ++i)
	{
		if(array[i] == m)
		{
			//to the left
			int j = i-1;
			while( array[j] > m && 
				   array[j] != m && 
				   j >=0 && 
				   j < n &&
				   !left_right)
			{
				left += array[j];
				j--;
			}
			
			left_right = false;
			
			//to the right
			int k = i+1;
			while( array[k] > m && k < n )
			{
				if( array[k] == m)
				{
					maximum = max(left + right + m, maximum);
					left = right;
					left_right = true;
					break;
				}
				right += array[k];
				k++;
			}
			
			if(!left_right)
			{
				maximum = max(left + right + m, maximum);
				left = 0;
			}
			
			right = 0;
			
			i = k - 1;
		}
	}
	cout << maximum <<endl;
}

int main(){
	int datasets, n,m, number_of_m;
	cin >> datasets;
	while( datasets != 0)
	{
		vector <int> array;
		cin >> n >> m;
		array.reserve(n+1);
		number_of_m = 0;
		for (int i = 0; i < n; ++i)
		{
			cin >> array[i];
			if( array[i] == m )
			{
				number_of_m++;
			}
		}
		
		calculate_maximum_subarray(n,m,array);
		
		
		datasets--;
	}
	
	return 0;
}