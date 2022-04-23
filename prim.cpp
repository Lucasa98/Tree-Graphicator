#include <iostream>
#include <map>
#include <tree.hpp>
#include <list>
#include <algorithm>
#include <limits>
#include <graphviz.hpp>
using namespace aed;
using namespace std;

typedef map<char, map<char, int>> graphW;

int prim(graphW& G, tree<char>& T){
	
	list<pair<char, char>> visited_a;
	list<char> visited_v;
	
	//buscamos la de menor peso
	pair<char, char> a_menor;
	int menor_peso = numeric_limits<int>::max();
	for(graphW::iterator it=G.begin(); it != G.end(); ++it){
		for(map<char, int>::iterator itM=it->second.begin(); itM != it->second.end(); ++itM){
			pair<char, char> aristaux = {it->first, itM->first};
			if(find(visited_a.begin(), visited_a.end(), aristaux) == visited_a.end() && itM->second < menor_peso){
				a_menor = aristaux;
				menor_peso = G[a_menor.first][a_menor.second];
			}
		}
	}
	visited_a.push_back(a_menor);
	visited_a.push_back({a_menor.second, a_menor.first});
	visited_v.push_back(a_menor.first);
	visited_v.push_back(a_menor.second);
	cout << a_menor.first << ' ' << a_menor.second << ' ' << menor_peso << endl;
	
	T.insert(T.begin(), a_menor.first);
	T.insert(T.begin().lchild(), a_menor.second);
	
	//Agregamos n-1 aristas
	for(size_t i=0; i<G.size()-3; ++i){
		
		//buscamos la de menor peso
		menor_peso = numeric_limits<int>::max();
		
		for(graphW::iterator it=G.begin(); it != G.end(); ++it){
			for(map<char, int>::iterator itM=it->second.begin(); itM != it->second.end(); ++itM){
				
				pair<char, char> evaluated_a = {it->first, itM->first};
				
				if(find(visited_a.begin(), visited_a.end(), evaluated_a) == visited_a.end() &&
				   itM->second < menor_peso &&
				   !(T.find(evaluated_a.first) != T.end() && T.find(evaluated_a.second) != T.end())
				   ){
					if(T.find(evaluated_a.first) != T.end()){
						T.insert(T.find(evaluated_a.first).lchild(), evaluated_a.second);
					}
					else if(T.find(evaluated_a.second) != T.end()){
						T.insert(T.find(evaluated_a.second).lchild(), evaluated_a.first);
					}
					a_menor = evaluated_a;
					menor_peso = G[a_menor.first][a_menor.second];
				}
			}
		}
		visited_a.push_back(a_menor);
		visited_a.push_back({a_menor.second, a_menor.first});
		visited_v.push_back(a_menor.first);
		visited_v.push_back(a_menor.second);
		cout << a_menor.first << ' ' << a_menor.second << ' ' << menor_peso << endl;
	}
	return 0;
}

int main() {
	
	graphW G = {
		{'A',{{'B',2},{'C',3}}},
		{'B',{{'A',2},{'D',5},{'E',2},{'C',1}}},
		{'C',{{'A',3},{'E',5},{'B',1}}},
		{'E',{{'C',5},{'B',2},{'D',1},{'Z',4}}},
		{'D',{{'B',5},{'E',1},{'Z',2}}},
		{'Z',{{'D',2},{'E',4}}}
	};
	tree<char> T;
	prim(G, T);
	tree2dot(T);
	
	return 0;
}







