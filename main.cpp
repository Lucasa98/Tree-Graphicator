#include <SFML/Graphics.hpp>
#include "Graphic.h"
#include "graphviz.hpp"
using namespace aed;
using namespace sf;

int main(){
	Graphic graphic;
	tree<char> T;
	lisp2tree("(a b c)", T);
	graphic.Play(T);
	
	return 0;
}

