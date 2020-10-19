#pragma once

#include "Drawable.h"

using namespace sf;
using namespace std;

class Node : public sf::Drawable{
private:
	CircleShape circle;
	vector<Node*> childs;
public:
	Node();
	Node(CircleShape);
	virtual void draw(RenderTarget&, RenderStates) const;
	
	void AddChild(Node&);
	Node& GetChild(std::size_t);
	void SetPosition(Vector2f);
	Vector2f GetPosition() const;
};
