#pragma once

#include "Drawable.h"

using namespace sf;

class Node : public sf::Drawable{
private:
	CircleShape circle;
public:
	Node();
	Node(CircleShape);
	virtual void draw(RenderTarget&, RenderStates) const;
};
