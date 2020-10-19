#include "Graphic.h"

Graphic::Graphic():
	w(VideoMode(640, 480), "Tree Graphicator"),
	nodePadre(),
	nodeHijo(){
	
	nodeHijo.SetPosition(Vector2f(500, 300));
	nodePadre.AddChild(nodeHijo);
	
	
	///Debug
	pos = Vector2f(500, 300);
}
void Graphic::Play(){
	while(w.isOpen()){
		ProcessEvents();
		
		/**
		Debug
		**/
		nodeHijo.SetPosition(pos);
		
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
	
	w.draw(nodePadre);
	w.draw(nodeHijo);
	
	w.display();
}
template<typename Q>
void Graphic::GraphTree(tree<Q> T){
	vector<Node> nodes = TreeManager<Q>::GenerateNodes(T);
}
