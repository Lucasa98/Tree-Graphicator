#pragma once

#include "Drawable.h"

using namespace sf;
using namespace std;

class Node : public sf::Drawable{
private:
	CircleShape circle;
	vector<Node*> childs;
	string symbol;
public:
	Node();
	Node(string);
	virtual void draw(RenderTarget&, RenderStates) const;
	
	///Modificar
	void AddChild(Node*);
	Node& GetChild(std::size_t);
	void SetSymbol(char);
	
	///Graficar
	void SetPosition(Vector2f);
	Vector2f GetPosition() const;
	Vector2f GetCenter() const;
};
