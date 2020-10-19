#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

namespace source{
	
class Drawable{
protected:
	virtual void Draw(RenderWindow*) =0;
};

}
