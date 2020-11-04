#pragma once

#include <map>
#include <sstream>
#include "tree.hpp"
#include "Node.h"
#include "helpers.h"

using namespace aed;
using namespace std;

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
