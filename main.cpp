#include <SFML/Graphics.hpp>
#include "Graphic.h"
using namespace aed;
using namespace sf;

int main(){
	Graphic graphic;
	tree<char> T;
	lisp2tree("(a (b d e) (c (f g h)))", T);
	graphic.Play(T);
	
	return 0;
}

