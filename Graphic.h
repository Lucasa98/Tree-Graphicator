#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Node.h"
#include "tree.hpp"
#include "TreeManager.h"

using namespace aed;
using namespace sf;

class Graphic {
private:
	RenderWindow w;
	Node nodePadre;
	Node nodeHijo;
	
	Vector2f pos;
public:
	Graphic();
	void Play();
	void ProcessEvents();
	void Draw();
	
	template<typename Q>
	void GraphTree(tree<Q>);
};
