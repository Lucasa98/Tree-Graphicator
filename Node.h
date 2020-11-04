#pragma once

#include <iostream>
#include "Drawable.h"

using namespace sf;
using namespace std;

class Node : public sf::Drawable{
private:
	/// -----Config-----
	int r = 20;
	int outlineThick = 2;
	float defaultPosX = 0.f;
	float defaultPosY = 0.f;
	string fontName = "fonts/RobotoMono.ttf";
	int charSize = 12;
	/// ----------------
	
	Font font;
	Text text;
	
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
	void SetSymbol(string);
	
	///Graficar
	void SetPosition(Vector2f);
	Vector2f GetPosition() const;
	Vector2f GetCenter() const;
	string GetSymbol();
};
