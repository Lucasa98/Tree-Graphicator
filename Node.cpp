#include "Node.h"

Node::Node(){	
	circle = CircleShape(50);
	circle.setFillColor(Color::Black);
	circle.setOutlineThickness(2);
	circle.setOutlineColor(Color::White);
	circle.setPosition(Vector2f(0.f, 0.f));
}
Node::Node(CircleShape c) : circle(c){}

void Node::draw(RenderTarget& w, RenderStates state = RenderStates::Default) const{
	vector<VertexArray> e(childs.size());
	
	for(size_t i = 0; i < e.size(); ++i){
		e[i].setPrimitiveType(LineStrip);
		e[i].resize(2);
		e[i][0].position = GetPosition();
		e[i][1].position = childs[i]->GetPosition();
	}
	
	for(size_t i = 0; i < e.size(); ++i){
		w.draw(e[i]);
	}
	w.draw(circle);
}

void Node::AddChild(Node& n){
	childs.push_back(&n);
}
Node& Node::GetChild(std::size_t i){
	return *(childs[i]);
}
void Node::SetPosition(Vector2f p){
	circle.setPosition(p);
}
Vector2f Node::GetPosition() const{
	return circle.getPosition();
}
