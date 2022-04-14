#include "Planet.h"
typedef sf::Vector2<double> Vector2d;
double dt;
double scale;

//default constructor
Planet::Planet(Vector2d pos, Vector2d vel, double radius, double mass, sf::Color col)
{
	this->pos = pos;
	this->vel = vel;
	this->radius = radius;
	this->mass = mass;

	sf::CircleShape shape;
	shape.setPosition(pos.x / scale, pos.y / scale);
	shape.setRadius(radius / scale);
	shape.setOrigin(radius / scale, radius / scale);
	shape.setFillColor(col);
	this->shape = shape;
}


//update current position, multiplying by the speed of time
void Planet::update()
{
	
	vel += acc * dt;
	pos += vel * dt;
	shape.setPosition(pos.x / scale, pos.y / scale);
	acc = { 0, 0 };
	
}

void Planet::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

Vector2d Planet::getPos()
{
	return pos / scale;
}



//calculate gravitational force between unique pairs of planets
void Planet::gravityCalc(std::vector<Planet>& planetArray)
{

	std::vector<Planet>::iterator it;
	bool hit = true;
	while(hit)
	{
		[&]
		{
			int plCount = planetArray.size();
			for (int i = 0; i < plCount; i++) 
			{
				for (int j = i + 1; j < plCount; j++)
				{

					Planet& pl1 = planetArray[i];
					Planet& pl2 = planetArray[j];
					Vector2d deltaPos = pl2.pos - pl1.pos;
					double R = pythagor(deltaPos);

					if (R < pl1.radius + pl2.radius)
					{
						//new planet
						planetArray.push_back(Planet( //доделать
							pl1.pos + deltaPos / pythagor(deltaPos) * pl2.radius,
							(pl1.vel * pl1.mass + pl2.vel * pl2.mass) / (pl1.mass + pl2.mass),
							pythagor(pl1.radius, pl2.radius),
							pl1.mass + pl2.mass,
							sf::Color::Green
						));
					

						// i always bigger than j
						planetArray.erase(planetArray.begin() + i);
						planetArray.erase(planetArray.begin() + j - 1);

						hit = true;
						return;
					}
					//if statement ends
				}
			}
			//unique planet pairs loop ends

			//if R > pl1.radius + pl2.radius for each pairs of planets we can quit while loop
			hit = false;
			
		}();
	}
	//collision detection ends

	int plCount = planetArray.size();
	for (int i = 0; i < plCount; i++)
	{
		for (int j = i + 1; j < plCount; j++)
		{
			Planet& pl1 = planetArray[i];
			Planet& pl2 = planetArray[j];

			Vector2d deltaPos = pl1.pos - pl2.pos;
			double R = pythagor(deltaPos);
			Vector2d Fvar = -G * deltaPos / pow(R, 3);
			pl1.acc += Fvar * pl2.mass;
			pl2.acc -= Fvar * pl1.mass;		
		}
	}



}

void Planet::planetLines(std::vector<Planet>& planetArray, sf::RenderWindow& window)
{
	int plCount = planetArray.size();
	for (int i = 0; i < plCount; i++)
	{
		for (int j = i + 1; j < plCount; j++)
		{
			Planet& pl1 = planetArray[i];
			Planet& pl2 = planetArray[j];
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(pl1.pos / scale), sf::Color(50, 50, 50)),
				sf::Vertex(sf::Vector2f(pl2.pos / scale), sf::Color(50, 50, 50))
			};
			window.draw(line, 2, sf::Lines);
		}
	}

}






