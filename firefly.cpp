#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cmath>
#include <unordered_map>

using namespace std;

int main(){
	
	int input, h, l, stalag,stalac;
	scanf("%d %d", &l,&h);
	if(l % 2 == 0){
		stalag = l/2;
		stalac = l/2;
	}
	else{
		stalag = (l-1)/2 + 1;
		stalac = (l-1)/2;
	}
		
	//Initialize the size, so that it becomes faster --> no need to regrow the vector.
	vector<int> stalactites (stalac), stalagmites (stalag);
	vector<int> hash_table (h+1); // hash_table is a bad name but whatever
	int stg = 0,stl = 0;
	for(int i = 0; i < l; ++i){
		scanf("%d",&input);
		if(i % 2 == 0){
			stalagmites[stg] = input;
			++stg;
		}
		else{
			stalactites[stl] = input;
			++stl;
		}
	}
	
	sort(stalactites.begin(), stalactites.end());
	sort(stalagmites.begin(), stalagmites.end());
	/*for(auto s : stalagmites)
		cout << s << " ";
	cout << endl;
	for(auto s : stalactites)
		cout << s << " ";
	*/
	
	int latest = 0, last = 0;
	for(int j = 0; j < stalagmites.size(); ++j){
		if(stalagmites[j] > latest){
			latest = stalagmites[j];
			hash_table[stalagmites[j]] = stalagmites.size() - j;
			
			if(latest-last > 1){
				for(int k = last+1; k < latest; ++k){
					hash_table[k] = stalagmites.size() - j;
					last = latest;
				}
			}
			else{
				last = latest;
			}
				
		}
	}
	
	int first = 0, last2 = 0;
	for(int j = 0; j < stalactites.size(); ++j){
		if(stalactites[j] > first){
			first = stalactites[j];
			hash_table[h - stalactites[j] + 1] = hash_table[h - stalactites[j] + 1] + stalactites.size() - j;
		
			if(first-last2 > 1){
				for(int k = last2 + 1; k < first; ++k){
					hash_table[h - k + 1] = hash_table[h - k + 1] + stalactites.size() - j;
					last2 = first;
				}
			}
			else{
				last2 = first;
			}
		}
	}

	int min_result = 500000;
	int levels = 0;	
	/*for(vector<int>::iterator it = hash_table.begin()+1; it!=hash_table.end();it++){
		min_result = min(min_result,(*it));
	}*/
	
	hash_table[0] = 500000;
	for(auto &h : hash_table) //Faster than iterator above according to robku
		min_result = min(min_result,h);
	
	/*for(vector<int>::iterator it = hash_table.begin()+1; it!=hash_table.end();it++){
		if((*it) == min_result)
			++levels;
	}*/
	
	for(auto &h : hash_table){ //Faster than iterator above according to robku
		if(h == min_result)
			++levels;
	}
		printf("%d %d", min_result,levels);	
	return 0;
}