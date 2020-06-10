#include<stdio.h>
#include<vector>
#include<iostream>
#include<string>
#include <unordered_map>

using namespace std;

typedef std::unordered_map<string,int> words;
typedef std::unordered_map<int,string> dict;

template<class containerType>
void printMapContent(containerType& map)
{
	cout << "Map start: "<<endl;
	for(auto it = map.begin(); it != map.end(); it++)
	{
		cout << it->first << " " << it->second <<endl;
	}
	cout << "Map end: "<<endl;
}

template<class containerType>
void printVector(containerType& map)
{
	//cout << "Vector start: "<<endl;
	for(auto it = map.begin(); it != map.end(); it++)
	{
		cout << *it << " ";
	}
}

void parseDefLine(string line, string& key, string& value)
{
	string space(" ");
	auto last_space_pos = line.find_last_of(space);
	key = line.substr(4, last_space_pos - 4);
	value = line.substr( last_space_pos + 1 );
}

vector<string> divideLine(string line) // could have passed a vector by reference by does not seem to be needed for performance.
{
	vector<string> parsed;
	size_t place(0);
	size_t pos(5);
	string space(" ");
	while( place < line.length() )
	{
		place = line.find( space, pos);
		if( place == string::npos || place >= line.length() || pos >= line.length() )
		{
			break;
		}

		parsed.push_back( line.substr( pos, place - pos ) );
		pos = place + 1;
	}
	return parsed;
}

void parseAndCalcLine(string line, words& word_map, dict& reverse_map )
{
	vector<string> parsed_line( divideLine( line ) );
	
	vector<string> copy_line(parsed_line);
	
	auto iter = word_map.find(parsed_line.front());
	
	if( iter == word_map.end() )
	{
	
		printVector(copy_line);
		cout << "= unknown" << endl;
		return;
	}
	
	parsed_line.erase( parsed_line.begin() );
	
	int sum(iter->second);
	
	while(parsed_line.size() != 0 )
	{
		string sign = parsed_line.front();
		parsed_line.erase( parsed_line.begin() );
		
		auto got1 = word_map.find(parsed_line.front());
		
		if( got1 == word_map.end() )
		{
			printVector(copy_line);
			cout << "= unknown" << endl;
			return;
		}
		
		parsed_line.erase( parsed_line.begin() ); 
		
		if( sign.compare("+") == 0 )
		{
			sum = sum + got1->second;// + got2->second;
		}
		if( sign.compare("-") == 0 )
		{
			sum = sum - got1->second;// - got2->second; 
		}
	}
	
	auto got = reverse_map.find( sum );
	if( got != reverse_map.end() ) // the sum equals a word. Output it.
	{
		printVector(copy_line);
		cout << "= " << got->second << endl;
		return;
	}
	else
	{
		printVector(copy_line);
		cout << "= unknown" << endl;
	}
}

void update(words& word_map, dict& reverse_map, string key, int value)
{

	auto got = word_map.find( key );
	if( got != word_map.end() ) // this word already exists, replace its value.
	{
		int key2 = got->second; // extract the int.
		reverse_map.erase(key2); //erase the old entry by key2.
		reverse_map[value] = key; // replace the old string with the new one.
			
		word_map.at( key ) = value; // replace int with new value.	
	}
	else
	{
		word_map.insert( make_pair(key, value ) );
		reverse_map.insert( make_pair(value, key) );
	}
}


int main()
{

words word_map;
dict reverse_map;
string plus("+");
string minus("-");
string line;

while(getline (cin,line) )
{
	string key;
	string value;
	
	if( line[0] == 'd' )
	{	
		parseDefLine(line, key, value);
		update( word_map, reverse_map, key, stoi(value) );
	}
	else if( line.substr(0,2).compare("ca") == 0 )
	{
		parseAndCalcLine(line, word_map, reverse_map);
	}
	else // clear
	{
		word_map.erase( word_map.begin(), word_map.end() );
		reverse_map.erase( reverse_map.begin(), reverse_map.end() );
	}
}
return 0;
}