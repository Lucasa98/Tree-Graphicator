#include "Graphic.h"

using namespace aed;

Graphic::Graphic():
	w(VideoMode(640, 480), "Tree Graphicator"){}

void Graphic::ProcessEvents(){
	Event e;
	while(w.pollEvent(e)){
		if(e.type == Event::Closed)
			w.close();
		if(e.type == Event::KeyReleased){
			if(e.key.code == Keyboard::Escape)
				w.close();
		}
	}
}
void Graphic::Draw(){
	w.clear();
	
	// -----Dibujar Nodos con aristas a hijos
	for(map<string, Node*>::iterator n = nodes.begin(); n != nodes.end(); ++n){
		w.draw(*(n->second));
	}
	
	w.display();
}
