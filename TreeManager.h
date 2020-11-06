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
		SetPositions(map_nodes, T);
		///----------------
		
		return map_nodes;
	}
	
	/**
	static void SetPositions(map<string, list<string>> M, string n, Vector2f middle){
		
	}
	
	static void SetPositions(map<string, Node*>& M, tree<Q> T){
		///creamos un mapa que asigna la lista de hijos a cada nodo y el ancho máximo que ocupan los hijos
		map<string, pair<float, list<string>>> HerytanceMap;
		herytanceMap(T, HerytanceMap);
		
		SetPositions(HerytanceMap, *(T.begin()), Vector2f(320.f, 0.f));
	}1
	**/
	
	static void SetPositions(map<string, Node*>& M, tree<Q> T){
		vector<list<string>> levels = listLevels(T);
		for(size_t i = 0; i < levels.size(); ++i){
			float y = i*(40+20);
			float w = (levels[i].size()*40) + (10*(levels[i].size()-1));
			float x = (640-w)/2;
			
			int count = 0;
			for(typename list<string>::iterator n = levels[i].begin(); n != levels[i].end(); ++n){
				M[*n]->SetPosition(Vector2f(x+count*(40+10), y));
				++count;
			}
		}
	}
	
};
