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
	
	static void SetPositions(map<string, Node*>& M, map<string, pair<int, list<string>>> MH, string n, Vector2f middle){
		M[n]->SetPosition(middle);
		
		float width = (40.f+10.f)*MH[n].first;
		
		list<string> childs = MH[n].second;
		
		float left = middle.x - (width/2.f);
		
		for(list<string>::iterator c = childs.begin(); c != childs.end(); ++c){
			float cwidth = (40.f+10.f)*MH[*c].first;
			
			Vector2f cmid = Vector2f(left + (cwidth/2.f), middle.y + 60);
			
			SetPositions(M, MH, *c, cmid);
			
			left += cwidth;
		}
	}
	
	static void SetPositions(map<string, Node*>& M, tree<Q> T){
		///creamos un mapa que asigna la lista de hijos a cada nodo y el ancho máximo que ocupan los hijos
		map<string, pair<int, list<string>>> HerytanceMap;
		herytanceMap(T, HerytanceMap);
		
		stringstream ss; ss << *(T.begin());
		string raiz; ss >> raiz;
		
		SetPositions(M, HerytanceMap, raiz, Vector2f(320.f, 0.f));
	}
	
	/*
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
	*/
};
