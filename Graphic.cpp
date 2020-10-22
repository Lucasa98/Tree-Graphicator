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
	
	for(map<string, Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it){
		w.draw(*(it->second));
	}
	
	w.display();
}
