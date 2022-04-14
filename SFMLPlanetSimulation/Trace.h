#pragma once
#include <SFML/Graphics.hpp>
typedef sf::Vector2<double> Vector2d;

class Trace
{
	Vector2d pos;
	int lifeTime;
	sf::Vertex vertex;
public:
	Trace(Vector2d pos, int lifeTime);
	void draw(sf::RenderWindow& window);
	void update();
	bool isDead();
};

