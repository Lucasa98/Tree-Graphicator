#include "Node.h"
using namespace std;

Node::Node(){
	font.loadFromFile(fontName);
	
	circle = CircleShape(r);
	circle.setFillColor(Color::Black);
	circle.setOutlineThickness(outlineThick);
	circle.setOutlineColor(Color::White);
	circle.setPosition(Vector2f(defaultPosX, defaultPosY));
}

void Node::draw(RenderTarget& w, RenderStates state = RenderStates::Default) const{
	vector<VertexArray> e(childs.size());
	
	// Definimos aristas a hijos
	for(size_t i = 0; i < e.size(); ++i){
		e[i].setPrimitiveType(LineStrip);
		e[i].resize(2);
		e[i][0].position = GetCenter();
		e[i][1].position = childs[i]->GetCenter();
	}
	
	// Dibujamos aristas a hijos
	for(size_t i = 0; i < e.size(); ++i){
		w.draw(e[i]);
	}
	w.draw(circle);
	w.draw(text);
}

///Modificar
void Node::AddChild(Node* n){
	childs.push_back(n);
}
Node& Node::GetChild(std::size_t i){
	return *(childs[i]);
}
void Node::SetSymbol(string s){
	symbol = s;
	text.setString(symbol);
	text.setFont(font);
	text.setCharacterSize(charSize);
	Vector2f c = this->GetCenter();
	text.setPosition(c.x - (text.getLocalBounds().width/2), c.y - (text.getLocalBounds().height));
}

///Transform
void Node::SetPosition(Vector2f p){
	circle.setPosition(p);
	Vector2f c = this->GetCenter();
	text.setPosition(c.x - (text.getLocalBounds().width/2), c.y - (text.getLocalBounds().height));
}
Vector2f Node::GetPosition() const{
	return circle.getPosition();
}
Vector2f Node::GetCenter() const{
	Vector2f c_pos = circle.getPosition();
	return Vector2f(c_pos.x + circle.getRadius(), c_pos.y + circle.getRadius());
}
string Node::GetSymbol(){
	return symbol;
}
