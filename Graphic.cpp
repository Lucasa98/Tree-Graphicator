#include "Graphic.h"

Graphic::Graphic():
	w(VideoMode(640, 480), "Tree Graphicator"),
	node(){
}
void Graphic::Play(){
	while(w.isOpen()){
		ProcessEvents();
		Draw();
	};
}
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
	
	w.draw(node, RenderStates::Default);
	
	w.display();
}
