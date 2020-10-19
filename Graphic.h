#pragma once

#include <SFML/Graphics.hpp>
#include "Node.h"

using namespace sf;

class Graphic {
private:
	RenderWindow w;
	Node node;
public:
	Graphic();
	void Play();
	void ProcessEvents();
	void Draw();
};
