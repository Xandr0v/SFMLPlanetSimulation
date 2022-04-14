#include "Trace.h"
typedef sf::Vector2<double> Vector2d;

Trace::Trace(Vector2d pos, int lifeTime)
{
	this->pos = pos;
	this->lifeTime = lifeTime;
	sf::Vertex vertex(sf::Vector2f(pos.x, pos.y), sf::Color::Red);
	

}
void Trace::draw(sf::RenderWindow& window)
{
	window.draw(&vertex, 1, sf::Points);
}

void Trace::update()
{
	lifeTime -= 1;
}

bool Trace::isDead()
{
	return (lifeTime < 0);
}
