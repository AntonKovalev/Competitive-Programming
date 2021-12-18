#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

//! Generates all substrings of a string,
//! starting with the longest substring. 
//! Example output, if printed, for "abcn":
//! abcn
//! abc
//! bcn
//! ab
//! bc
//! cn
//! a
//! b
//! c
//! n

void generate(string str, vector<string>& genVec)
{
    int n = str.length();
    genVec.reserve(n*(n+1)/2);// simple arithmetic sum
    auto end = str.length();
    while(end != 0)
    {
       auto tmp_end = end;
       int i = 0;
       do
       {
           auto sub = str.substr(i, tmp_end - i);
           genVec.push_back(sub);
           //cout << sub << endl;

           tmp_end++;
           i++;
       } while(tmp_end <= str.length());

        end--;
    }
    return;
}

int main()
{

int n;

cin >> n;
vector<string> strings;
strings.reserve(n+1);
string str;
// Put all n strings into a vector.
for(auto i = 0; i < n; ++i)
{
    cin >> str;
    strings.push_back(str);
}

string minStr = *min_element(strings.begin(),
                             strings.end(),
                             [&](auto& str1, auto& str2){
    return str1.length() < str2.length();
});

vector<string> genVec;
generate(minStr, genVec);
bool done = false;
int length = 0;
for(int j = 0; !done && (j < genVec.size()); ++j)
{
    string substr = genVec[j];
    // Check if this substring is present in all other 
    // strings. If yes, we are done.
    // If it is not present in one string,
    // it cannot be the longest common substring
    // for all strings. Therefore, break this loop
    // and try a new substring.
    for(int i = 0; i < n; ++i)
    {
        auto found = strings[i].find(substr);
        if(found == string::npos)
        {
            break;
        }
        if(i == n-1)
        {
            // Here, we have looped over all
            // strings and substr was present in 
            // all of them. Therefore, we found
            // the longest substring.
            done = true;
            length = substr.length();
        }
    }
}
cout << length;
    return 0;
}