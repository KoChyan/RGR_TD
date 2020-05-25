#pragma once
#include <SFML/Graphics.hpp>

class MyMap
{
private:
	sf::Texture mapT;
	sf::Sprite mapS;
public:
	MyMap() {
		mapT.loadFromFile("textures/myMap.png");
		mapS.setTexture(mapT);
	}
	sf::Sprite getSprite() {
		return mapS;
	}
};

