#pragma once
#include <SFML/Graphics.hpp>
class Trace
{
	sf::Vector2f pos;
	int lifeTime;
	sf::Vertex vertex;
public:
	Trace(sf::Vector2f pos, int lifeTime);
	void draw(sf::RenderWindow& window);
	bool update();
};

