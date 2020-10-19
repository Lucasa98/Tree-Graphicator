#include "Node.h"

Node::Node(){
	circle = CircleShape(50);
	circle.setFillColor(Color::Black);
	circle.setOutlineThickness(5);
	circle.setOutlineColor(Color::White);
	circle.setPosition(Vector2f(0.f, 0.f));
}
Node::Node(CircleShape c) : circle(c){}

void Node::draw(RenderTarget& w, RenderStates state = RenderStates::Default) const{
	w.draw(circle, state);
}
