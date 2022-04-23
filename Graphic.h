#pragma once

#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Node.h"
#include "tree.hpp"
#include "lisp.hpp"
#include "TreeManager.h"

using namespace std;
using namespace aed;
using namespace sf;

class Graphic {
private:
	RenderWindow w;
	map<string, Node*> nodes;
	
public:
	Graphic();
	template<typename Q>
	void Play(tree<Q> T){
		
		this->GraphTree(T);
		
		while(w.isOpen()){
			ProcessEvents();
			Draw();
		};
	}
	void ProcessEvents();
	void Draw();
	
	template<typename Q>
	void GraphTree(tree<Q> T){
		nodes = TreeManager<Q>::GenerateNodes(T);
	}
};
