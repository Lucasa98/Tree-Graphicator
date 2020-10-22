#pragma once

#include <sstream>
#include <vector>
#include <map>
#include <ctime>
#include "helpers.h"
#include "tree.hpp"
#include "Node.h"

using namespace std;
using namespace aed;

template<typename Q>
class TreeManager{
private:
	friend class Node;
public:
	bool LoadTree(tree<Q>);
	///wrapper
	static map<string, Node*> GenerateNodes(tree<Q> T){
		srand(time(0));
		
		///Transformar tree en map
		map<string, Node*> map_nodes;
		tree2map(T, map_nodes);
		///-------------
		
		///Posicionar Nodos
		for(map<string, Node*>::iterator it = map_nodes.begin(); it != map_nodes.end(); ++it){
			float x = rand()%640;
			float y = rand()%480;
			it->second->SetPosition(Vector2f(x, y));
		}
		///----------------
		
		return map_nodes;
	}
};
