#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{

int n;
cin >> n;
int row, col;
while(n != 0)
{
 cin >> row >> col;
 uint64_t ans = 1;
 

 for(auto i = 0; i < (row + col); ++i)
 {
 	ans *= 3;
 	ans = ans % 1000000007;
 }
 
 for(auto i = 0; i < (row * col); ++i)
 {
 	ans *= 2;
 	ans = ans % 1000000007;
 }
 
 cout << ans <<endl;

n--;
}

return 0;
}
