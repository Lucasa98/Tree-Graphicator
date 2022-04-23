#include <SFML/Graphics.hpp>
#include "Graphic.h"
using namespace aed;
using namespace sf;

int main(){
	Graphic graphic;
	tree<int> T;
	lisp2tree("(1 (2 6 7 8) 3 (4 (9 12)) (5 10 11))", T);
	graphic.Play(T);
	
	return 0;
}
