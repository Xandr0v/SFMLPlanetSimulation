#include "Trace.h"

Trace::Trace(sf::Vector2f pos, int lifeTime)
{
	this->pos = pos;
	this->lifeTime = lifeTime;
	sf::Vertex vertex(pos, sf::Color::Red);
	this->vertex = vertex;

}
void Trace::draw(sf::RenderWindow& window)
{
	window.draw(&vertex, 1, sf::Points);
}

bool Trace::update()
{
	this->lifeTime -= 1;
	if (lifeTime < 0)
	{
		return true;
	}
	return false;
}
