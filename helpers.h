#pragma once

#include <map>
#include <list>
#include <sstream>
#include "tree.hpp"
#include "Node.h"

using namespace aed;
using namespace std;

///Auxiliar
template<typename Q>
tree<string>::iterator treeQ2treestring(tree<Q> TQ, tree<string>& T, tree<string>::iterator n, typename tree<Q>::iterator nq){
	stringstream ss; ss << *nq;
	string s; ss >> s;
	
	n = T.insert(n, s);
	
	typename tree<Q>::iterator cq = nq.lchild();
	tree<string>::iterator c = n.lchild();
	
	while(cq != TQ.end()){
		c = treeQ2treestring(TQ, T, c, cq++);
		c++;
	}
	return n;
}
///Wrapper
template<typename Q>
void treeQ2treestring(tree<Q> TQ, tree<string>& Ts){
	Ts.clear();
	if(TQ.begin() != TQ.end()){
		treeQ2treestring(TQ, Ts, Ts.begin(), TQ.begin());
	}
}

///Auxiliar Devuelve el ancho
template<typename Q>
int herytanceMap(tree<string>& T, map<string,pair<int, list<string>>>& M, tree<string>::iterator n){
	list<string> Laux;
	M[*n].second = Laux;
	
	int width = 0;
	
	tree<string>::iterator c = n.lchild();
	
	while(c != T.end()){
		M[*n].second.push_back(*c);
		width += herytanceMap<Q>(T, M, c);
		++c;
	}
	
	if(width == 0){
		M[*n].first = 1;
		return 1;
	}
	
	M[*n].first = width;
	return width;
}
///Wrapper
template<typename Q>
void herytanceMap(tree<Q>& T,map<string,pair<int, list<string>>>& M) {
	M.clear();
	
	if(T.begin() != T.end()){
		tree<string> Ts;
		treeQ2treestring(T, Ts);
		herytanceMap<Q>(Ts, M, Ts.begin());
	}
}
	
///Wrapper
//template<typename Q>
//map<string, list<string>> tree2herytancemap(tree<Q>& TQ){
//	map<string, list<string>> M;
//	if(TQ.begin() != TQ.end()){
//		tree<string> T = treeQ2treestring(TQ);
//		tree2herytancemap(T, M, T.begin());
//	}
//	return M;
//}

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
