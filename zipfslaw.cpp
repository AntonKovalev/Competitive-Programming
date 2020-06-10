#include <vector>
#include<iostream>
#include<algorithm>
#include <stdio.h>
#include <ctype.h> // std::tolower
#include <unordered_map>
#include <utility>      // std::pair, std::make_pair
#include <sstream>
#include<string>
#include<fstream>

using namespace std;

typedef unordered_map<string, int> stringmap;// word and the number of such words encountered.

int main()
{
string line;
int number;
while(1 == scanf("%d",&number))
{
stringmap hashtable;
getline(cin, line);
while( line.compare("EndOfText") != 0 ) 
{
string word = "";
for(int i = 0; i < line.length(); ++i )
{
	if( ( int(line[i]) > 64 && int(line[i]) < 91 ) || // Capital letter or...
		( int(line[i]) > 96 && int(line[i]) < 123 ) ) // ...Non-capital letter.
		{
			word = word + line[i];
		}
		else
		{
			 // This iteration went through a letter. Next time we hit a non-letter, we shall extract a word.
			if( word.compare("") != 0 )
			{
				transform(word.begin(), word.end(), word.begin(), ::tolower);
				auto iterator = hashtable.find(word);
				
				if( iterator == hashtable.end() ) // not found, insert
				{
					hashtable.insert( make_pair(word, 1) );
				}
				else // this word already exists, add 1 to its value.
				{
					iterator->second++;
				}
				
				word = "";
			}
		}
}

if( word.compare("") != 0 )
{
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		auto iterator = hashtable.find(word);
				
		if( iterator == hashtable.end() ) // not found, insert
		{
			hashtable.insert( make_pair(word, 1) );
		}
		else // this word already exists, add 1 to its value.
		{
			iterator->second++;
		}
}
getline(cin, line);
}
bool found = false;
vector<string> names;
for( auto it = hashtable.begin(); it != hashtable.end(); ++it)
{
	if( it->second == number )
	{
		found = true;
		names.push_back(it->first);
	}
}
if( !found ) 
{
	cout << "There is no such word."<< endl;
}
else
{
	sort(names.begin(), names.end() );
	for( auto it = names.begin(); it != names.end(); ++it)
	{
		cout << *it << endl;
	}
}
}
return 0;
}
