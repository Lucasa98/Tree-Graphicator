#include <SFML/Graphics.hpp>
#include "Graphic.h"
using namespace aed;
using namespace sf;

int main(){
	Graphic graphic;
	tree<string> T;
	lisp2tree("(Source (Fuentes Graphics main Node) (Cabeceras Drawable.h Graphic.h helpers.h Node.h TreeManager.h))", T);
	graphic.Play(T);
	
	return 0;
}

