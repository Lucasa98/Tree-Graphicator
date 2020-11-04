#include <iostream>
#include <map>
#include <tree.hpp>
#include <list>
#include <algorithm>
#include <limits>
#include <graphviz.hpp>
#include <chrono>
#include <unistd.h>
using namespace aed;
using namespace std;

typedef map<char, map<char, int>> graphW;

int prim(graphW& G, tree<char>& T){
	T.clear();
	
	int peso = 0;
	
	list<char> visited_v;
	T.insert(T.begin(), G.begin()->first);
	visited_v.push_back(G.begin()->first);
	size_t nodos = 1;
	
	while(nodos < G.size()){
		
		//Encontramos la arista incidente a un nodo visitado que tenga el menor peso
		pair<char, char> menor_a = {G.begin()->first, G.begin()->second.begin()->first};
		int peso_a = numeric_limits<int>::max();
		for(list<char>::iterator nit = visited_v.begin(); nit != visited_v.end(); ++nit){
			for(map<char, int>::iterator adyit = G[*nit].begin(); adyit != G[*nit].end(); ++adyit){
				
				//Si la arista tiene menor peso y no pertenecen ambos nodos al arbol, cambiamos la menor
				if(	adyit->second < peso_a &&
					T.find(adyit->first) == T.end()
				   ){
					menor_a = {*nit, adyit->first};
					peso_a = G[menor_a.first][menor_a.second];
				}
			}
		}
		
		//insertamos la arista encontrada en el arbol
		T.insert(T.find(menor_a.first).lchild(), menor_a.second);
		cout << menor_a.first << ' ' << menor_a.second << ' ' << G[menor_a.first][menor_a.second] << endl;
		visited_v.push_back(menor_a.second);
		++nodos;
		peso += G[menor_a.first][menor_a.second];
	}
	return peso;
}

int kruskal(graphW& G, tree<char>& T){
	T.clear();
	
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
	
	size_t cant_nodos = 2;
	T.insert(T.begin(), a_menor.first);
	T.insert(T.begin().lchild(), a_menor.second);
	list<tree<char>> TT;
	TT.push_back(T);
	
	//Agregamos n-2 aristas (mas la que agregue recien como base)
	for(size_t i=0; i<G.size()-2; ++i){
		
		//buscamos la de menor peso
		menor_peso = numeric_limits<int>::max();
		
		for(graphW::iterator it=G.begin(); it != G.end(); ++it){
			for(map<char, int>::iterator itM=it->second.begin(); itM != it->second.end(); ++itM){
				
				pair<char, char> evaluated_a = {it->first, itM->first};
				
				//Es menor de todos si: el peso es menor que todas, no fue visitada y no crean un bucle en ningun arbol
				if(find(visited_a.begin(), visited_a.end(), evaluated_a) == visited_a.end() &&
				   itM->second < menor_peso
				   ){
					bool esBucle = false;
					for(list<tree<char>>::iterator TTit = TT.begin(); TTit != TT.end(); ++TTit){
						if(TTit->find(evaluated_a.first) != TTit->end() && TTit->find(evaluated_a.second) != TTit->end())
							esBucle = true;
					}
					if(!esBucle){
						a_menor = evaluated_a;
						menor_peso = G[a_menor.first][a_menor.second];
					}
				}
			}
		}
		
		//Si uno esta en algun arbol, agrega el otro como hijo de ese, en ese arbol. Y encontrado pasa a true
		bool encontrado = false;
		
		for(list<tree<char>>::iterator TTit = TT.begin(); TTit != TT.end(); ++TTit){
			if(!encontrado){
				if(TTit->find(a_menor.first) != TTit->end()){
					TTit->insert(TTit->find(a_menor.first).lchild(), a_menor.second);
					encontrado = true;
					if(TTit == TT.begin()) ++cant_nodos;
				}
				else if(TTit->find(a_menor.second) != TTit->end()){
					TTit->insert(TTit->find(a_menor.second).lchild(), a_menor.first);
					encontrado = true;
					if(TTit == TT.begin()) ++cant_nodos;
				}
			}
		}
		if(!encontrado){
			tree<char> Taux;
			Taux.insert(Taux.begin(), a_menor.first);
			Taux.insert(Taux.begin().lchild(), a_menor.second);
			TT.push_back(Taux);
		}
		
		visited_a.push_back(a_menor);
		visited_a.push_back({a_menor.second, a_menor.first});
		visited_v.push_back(a_menor.first);
		visited_v.push_back(a_menor.second);
		cout << a_menor.first << ' ' << a_menor.second << ' ' << menor_peso << endl;
	}
	
	//Agregamos las demas aristas al arbol
	cout << "nodos: " << cant_nodos << " vertices: " << G.size() << endl;
	while(cant_nodos < G.size()){
		cout << "nodos: " << cant_nodos << " vertices: " << G.size() << endl;
		for(list<pair<char,char>>::iterator it = visited_a.begin(); it != visited_a.end(); ++it){
			if(!(T.find(it->first) != T.end() && T.find(it->second) != T.end())){
				if(T.find(it->first) != T.end()){
					T.insert(T.find(it->first).lchild(), it->second);
					++cant_nodos;
				}
				else if(T.find(it->first) != T.end()){
					T.insert(T.find(it->second).lchild(), it->first);
					++cant_nodos;
				}
			}
		}
	}
	
	return 0;
}


int main() {
	
	graphW G = {
		{'A',{{'B',2},{'C',3},{'F',3}}},
		{'B',{{'A',2},{'D',5},{'E',20},{'G',2}}},
		{'C',{{'A',3},{'E',5}}},
		{'E',{{'C',5},{'B',20},{'D',1},{'Z',4}}},
		{'D',{{'B',5},{'E',1},{'Z',2}}},
		{'Z',{{'D',2},{'E',4}}},
		{'F',{{'A',3},{'G',3}}},
		{'G',{{'B',2},{'F',3}}},
	};
	tree<char> T;
	
	auto t0 = chrono::steady_clock::now();
	//kruskal(G, T);
	cout << "peso: " << prim(G, T) << endl;
	auto t1 = chrono::steady_clock::now();
	cout << "Tiempo: " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << " milisegundos" << endl;
	tree2dot(T);
	
	return 0;
}







