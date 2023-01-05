#include<vector>
#include<iostream>
#include<string>
#include <bitset>
#include <math.h>

using namespace std;

long long grayToBinary (string& gray) 
{	
	string n = string(1,gray[0]);

    for (int i = 1; i < gray.length(); i++)
    {
        if (gray[i] == n[i-1])
            n += "0";
        else
            n += "1";
    }

    return stoll(n,nullptr,2);
}

int main()
{

int n;
string a,b;

cin >> n >> a >> b;

long long idx_a = grayToBinary(a);
long long idx_b = grayToBinary(b);

cout << abs(idx_b - idx_a) - 1;

return 0;
}
