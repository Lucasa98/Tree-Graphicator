#pragma once

#include <map>
#include <sstream>
#include "tree.hpp"
#include "Node.h"
#include "helpers.h"

using namespace aed;
using namespace std;

template<typename Q>
int altura(tree<Q> T, typename tree<Q>::iterator n, int dist_n){
	if(n.lchild() == T.end()) return dist_n;

	typename tree<Q>::iterator c = n.lchild();
	int mayor = altura(T, c++, dist_n+1);
	while(c != T.end()){
		int alt_c = altura(T, c++, dist_n+1);
		if(alt_c > mayor) mayor = alt_c;
	}
	return mayor;
}
template<typename Q>
int altura(tree<Q> T){
	return altura(T, T.begin(), 0);
}

///Auxiliar
template<typename Q>
void listLevels(tree<Q> T, vector<list<string>>& levels, typename tree<Q>::iterator n, size_t level){
	stringstream ss; ss << *n;
	string s; ss >> s;
	levels[level].push_back(s);
	
	typename tree<Q>::iterator c = n.lchild();
	
	while(c != T.end()){
		listLevels(T, levels, c, level+1);
		c++;
	}
}
///Wrapper
template<typename Q>
vector<list<string>> listLevels(tree<Q> T){
	vector<list<string>> levels;
	if(T.begin() != T.end()){
		int alt = altura(T);
		levels.resize(alt+1);
		listLevels(T, levels, T.begin(), 0);
		return levels;
	}
	return levels;
}

///Auxiliar
template<typename Q>
Node* tree2map(tree<Q> T, typename tree<Q>::iterator n, map<string, Node*>& nodes){
	stringstream ss; ss << *n;
	string s; ss >> s;
	
	Node* node = new Node();
	node->SetSymbol(s);
	nodes[s] = node;
	
	typename tree<Q>::iterator c = n.lchild();
	
	while(c != T.end()){
		node->AddChild(tree2map(T, c++, nodes));
	}
	return node;
}
///Wrapper
template<typename Q>
void tree2map(tree<Q> T, map<string, Node*>& nodes){
	if(T.begin() != T.end()){
		tree2map(T, T.begin(), nodes);
	}
}
